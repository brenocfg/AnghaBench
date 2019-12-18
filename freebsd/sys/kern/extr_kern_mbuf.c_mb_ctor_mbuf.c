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
struct mbuf {int dummy; } ;
struct mb_args {short type; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 short MT_NOINIT ; 
 int M_NOFREE ; 
 int m_init (struct mbuf*,int,short,int) ; 
 int /*<<< orphan*/  trash_ctor (void*,int,void*,int) ; 

__attribute__((used)) static int
mb_ctor_mbuf(void *mem, int size, void *arg, int how)
{
	struct mbuf *m;
	struct mb_args *args;
	int error;
	int flags;
	short type;

#ifdef INVARIANTS
	trash_ctor(mem, size, arg, how);
#endif
	args = (struct mb_args *)arg;
	type = args->type;

	/*
	 * The mbuf is initialized later.  The caller has the
	 * responsibility to set up any MAC labels too.
	 */
	if (type == MT_NOINIT)
		return (0);

	m = (struct mbuf *)mem;
	flags = args->flags;
	MPASS((flags & M_NOFREE) == 0);

	error = m_init(m, how, type, flags);

	return (error);
}