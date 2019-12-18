#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rt_sigframe_user_layout {size_t limit; size_t size; unsigned long extra_offset; } ;
struct extra_context {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t EXTRA_CONTEXT_SIZE ; 
 size_t SIGFRAME_MAXSZ ; 
 size_t TERMINATOR_SIZE ; 
 size_t round_up (size_t,int) ; 

__attribute__((used)) static int __sigframe_alloc(struct rt_sigframe_user_layout *user,
			    unsigned long *offset, size_t size, bool extend)
{
	size_t padded_size = round_up(size, 16);

	if (padded_size > user->limit - user->size &&
	    !user->extra_offset &&
	    extend) {
		int ret;

		user->limit += EXTRA_CONTEXT_SIZE;
		ret = __sigframe_alloc(user, &user->extra_offset,
				       sizeof(struct extra_context), false);
		if (ret) {
			user->limit -= EXTRA_CONTEXT_SIZE;
			return ret;
		}

		/* Reserve space for the __reserved[] terminator */
		user->size += TERMINATOR_SIZE;

		/*
		 * Allow expansion up to SIGFRAME_MAXSZ, ensuring space for
		 * the terminator:
		 */
		user->limit = SIGFRAME_MAXSZ - TERMINATOR_SIZE;
	}

	/* Still not enough space?  Bad luck! */
	if (padded_size > user->limit - user->size)
		return -ENOMEM;

	*offset = user->size;
	user->size += padded_size;

	return 0;
}