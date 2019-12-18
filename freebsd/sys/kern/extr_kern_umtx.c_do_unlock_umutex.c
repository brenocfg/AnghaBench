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
typedef  int uint32_t ;
struct umutex {int /*<<< orphan*/  m_flags; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  UMUTEX_PRIO_INHERIT 129 
#define  UMUTEX_PRIO_PROTECT 128 
 int do_unlock_normal (struct thread*,struct umutex*,int,int) ; 
 int do_unlock_pi (struct thread*,struct umutex*,int,int) ; 
 int do_unlock_pp (struct thread*,struct umutex*,int,int) ; 
 int fueword32 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
do_unlock_umutex(struct thread *td, struct umutex *m, bool rb)
{
	uint32_t flags;
	int error;

	error = fueword32(&m->m_flags, &flags);
	if (error == -1)
		return (EFAULT);

	switch (flags & (UMUTEX_PRIO_INHERIT | UMUTEX_PRIO_PROTECT)) {
	case 0:
		return (do_unlock_normal(td, m, flags, rb));
	case UMUTEX_PRIO_INHERIT:
		return (do_unlock_pi(td, m, flags, rb));
	case UMUTEX_PRIO_PROTECT:
		return (do_unlock_pp(td, m, flags, rb));
	}

	return (EINVAL);
}