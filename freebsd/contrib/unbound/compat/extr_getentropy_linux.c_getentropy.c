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
 scalar_t__ EIO ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ errno ; 
 int getentropy_fallback (void*,size_t) ; 
 int getentropy_getrandom (void*,size_t) ; 
 int getentropy_sysctl (void*,size_t) ; 
 int getentropy_urandom (void*,size_t) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 

int
getentropy(void *buf, size_t len)
{
	int ret = -1;

	if (len > 256) {
		errno = EIO;
		return -1;
	}

#if defined(SYS_getrandom) && defined(__NR_getrandom)
	/*
	 * Try descriptor-less getrandom()
	 */
	ret = getentropy_getrandom(buf, len);
	if (ret != -1)
		return (ret);
	if (errno != ENOSYS)
		return (-1);
#endif

	/*
	 * Try to get entropy with /dev/urandom
	 *
	 * This can fail if the process is inside a chroot or if file
	 * descriptors are exhausted.
	 */
	ret = getentropy_urandom(buf, len);
	if (ret != -1)
		return (ret);

#ifdef SYS__sysctl
	/*
	 * Try to use sysctl CTL_KERN, KERN_RANDOM, RANDOM_UUID.
	 * sysctl is a failsafe API, so it guarantees a result.  This
	 * should work inside a chroot, or when file descriptors are
	 * exhausted.
	 *
	 * However this can fail if the Linux kernel removes support
	 * for sysctl.  Starting in 2007, there have been efforts to
	 * deprecate the sysctl API/ABI, and push callers towards use
	 * of the chroot-unavailable fd-using /proc mechanism --
	 * essentially the same problems as /dev/urandom.
	 *
	 * Numerous setbacks have been encountered in their deprecation
	 * schedule, so as of June 2014 the kernel ABI still exists on
	 * most Linux architectures. The sysctl() stub in libc is missing
	 * on some systems.  There are also reports that some kernels
	 * spew messages to the console.
	 */
	ret = getentropy_sysctl(buf, len);
	if (ret != -1)
		return (ret);
#endif /* SYS__sysctl */

	/*
	 * Entropy collection via /dev/urandom and sysctl have failed.
	 *
	 * No other API exists for collecting entropy.  See the large
	 * comment block above.
	 *
	 * We have very few options:
	 *     - Even syslog_r is unsafe to call at this low level, so
	 *	 there is no way to alert the user or program.
	 *     - Cannot call abort() because some systems have unsafe
	 *	 corefiles.
	 *     - Could raise(SIGKILL) resulting in silent program termination.
	 *     - Return EIO, to hint that arc4random's stir function
	 *       should raise(SIGKILL)
	 *     - Do the best under the circumstances....
	 *
	 * This code path exists to bring light to the issue that Linux
	 * does not provide a failsafe API for entropy collection.
	 *
	 * We hope this demonstrates that Linux should either retain their
	 * sysctl ABI, or consider providing a new failsafe API which
	 * works in a chroot or when file descriptors are exhausted.
	 */
#undef FAIL_INSTEAD_OF_TRYING_FALLBACK
#ifdef FAIL_INSTEAD_OF_TRYING_FALLBACK
	raise(SIGKILL);
#endif
	ret = getentropy_fallback(buf, len);
	if (ret != -1)
		return (ret);

	errno = EIO;
	return (ret);
}