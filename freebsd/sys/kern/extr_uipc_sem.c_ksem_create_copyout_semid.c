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
struct thread {int dummy; } ;
typedef  int semid_t ;
typedef  int /*<<< orphan*/  semid32 ;
typedef  int /*<<< orphan*/  semid ;
typedef  int int32_t ;

/* Variables and functions */
 int copyout (void*,int*,size_t) ; 

__attribute__((used)) static int
ksem_create_copyout_semid(struct thread *td, semid_t *semidp, int fd,
    int compat32)
{
	semid_t semid;
#ifdef COMPAT_FREEBSD32
	int32_t semid32;
#endif
	void *ptr;
	size_t ptrs;

#ifdef COMPAT_FREEBSD32
	if (compat32) {
		semid32 = fd;
		ptr = &semid32;
		ptrs = sizeof(semid32);
	} else {
#endif
		semid = fd;
		ptr = &semid;
		ptrs = sizeof(semid);
		compat32 = 0; /* silence gcc */
#ifdef COMPAT_FREEBSD32
	}
#endif

	return (copyout(ptr, semidp, ptrs));
}