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
struct val_env {int nsec3_keyiter_count; size_t* nsec3_keysize; size_t* nsec3_maxiter; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static size_t
get_max_iter(struct val_env* ve, size_t bits)
{
	int i;
	log_assert(ve->nsec3_keyiter_count > 0);
	/* round up to nearest config keysize, linear search, keep it small */
	for(i=0; i<ve->nsec3_keyiter_count; i++) {
		if(bits <= ve->nsec3_keysize[i])
			return ve->nsec3_maxiter[i];
	}
	/* else, use value for biggest key */
	return ve->nsec3_maxiter[ve->nsec3_keyiter_count-1];
}