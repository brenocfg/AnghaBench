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
struct __sysctl_args {int* name; int nlen; char* oldval; size_t* oldlenp; } ;

/* Variables and functions */
#define  CTL_KERN 130 
 int EIO ; 
#define  KERN_RANDOM 129 
#define  RANDOM_UUID 128 
 int /*<<< orphan*/  SYS__sysctl ; 
 int errno ; 
 scalar_t__ gotdata (void*,size_t) ; 
 size_t min (size_t,int) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,struct __sysctl_args*) ; 

__attribute__((used)) static int
getentropy_sysctl(void *buf, size_t len)
{
	static int mib[] = { CTL_KERN, KERN_RANDOM, RANDOM_UUID };
	size_t i;
	int save_errno = errno;

	for (i = 0; i < len; ) {
		size_t chunk = min(len - i, 16);

		/* SYS__sysctl because some systems already removed sysctl() */
		struct __sysctl_args args = {
			.name = mib,
			.nlen = 3,
			.oldval = (char *)buf + i,
			.oldlenp = &chunk,
		};
		if (syscall(SYS__sysctl, &args) != 0)
			goto sysctlfailed;
		i += chunk;
	}
	if (gotdata(buf, len) == 0) {
		errno = save_errno;
		return (0);			/* satisfied */
	}
sysctlfailed:
	errno = EIO;
	return -1;
}