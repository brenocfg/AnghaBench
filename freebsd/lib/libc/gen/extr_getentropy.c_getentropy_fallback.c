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

/* Variables and functions */
 scalar_t__ EFAULT ; 
 int /*<<< orphan*/  _getentropy_fail () ; 
 size_t arnd_sysctl (void*,size_t) ; 
 scalar_t__ errno ; 

__attribute__((used)) static int
getentropy_fallback(void *buf, size_t buflen)
{
	/*
	 * oldp (buf) == NULL has a special meaning for sysctl that results in
	 * no EFAULT.  For compatibility with the kernel getrandom(2), detect
	 * this case and return the appropriate error.
	 */
	if (buf == NULL && buflen > 0) {
		errno = EFAULT;
		return (-1);
	}
	if (arnd_sysctl(buf, buflen) != buflen) {
		if (errno == EFAULT)
			return (-1);
		/*
		 * This cannot happen.  arnd_sysctl() spins until the random
		 * device is seeded and then repeatedly reads until the full
		 * request is satisfied.  The only way for this to return a zero
		 * byte or short read is if sysctl(2) on the kern.arandom MIB
		 * fails.  In this case, excepting the user-provided-a-bogus-
		 * buffer EFAULT, give up (like for arc4random(3)'s arc4_stir).
		 */
		_getentropy_fail();
	}
	return (0);
}