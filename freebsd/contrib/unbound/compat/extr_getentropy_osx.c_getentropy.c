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
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  errno ; 
 int getentropy_fallback (void*,size_t) ; 
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

	/*
	 * Try to get entropy with /dev/urandom
	 *
	 * This can fail if the process is inside a chroot or if file
	 * descriptors are exhausted.
	 */
	ret = getentropy_urandom(buf, len);
	if (ret != -1)
		return (ret);

	/*
	 * Entropy collection via /dev/urandom and sysctl have failed.
	 *
	 * No other API exists for collecting entropy, and we have
	 * no failsafe way to get it on OSX that is not sensitive
	 * to resource exhaustion.
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
	 * This code path exists to bring light to the issue that OSX
	 * does not provide a failsafe API for entropy collection.
	 *
	 * We hope this demonstrates that OSX should consider
	 * providing a new failsafe API which works in a chroot or
	 * when file descriptors are exhausted.
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