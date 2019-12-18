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
typedef  uintptr_t uint32_t ;
typedef  uintptr_t u_long ;
struct thread {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fueword (void*,uintptr_t*) ; 
 int fueword32 (void*,uintptr_t*) ; 

__attribute__((used)) static int
umtx_read_uptr(struct thread *td, uintptr_t ptr, uintptr_t *res)
{
	u_long res1;
#ifdef COMPAT_FREEBSD32
	uint32_t res32;
#endif
	int error;

#ifdef COMPAT_FREEBSD32
	if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
		error = fueword32((void *)ptr, &res32);
		if (error == 0)
			res1 = res32;
	} else
#endif
	{
		error = fueword((void *)ptr, &res1);
	}
	if (error == 0)
		*res = res1;
	else
		error = EFAULT;
	return (error);
}