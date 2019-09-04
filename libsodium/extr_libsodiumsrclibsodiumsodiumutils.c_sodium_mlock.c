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
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 

int
sodium_mlock(void *const addr, const size_t len)
{
#if defined(MADV_DONTDUMP) && defined(HAVE_MADVISE)
    (void) madvise(addr, len, MADV_DONTDUMP);
#endif
#ifdef HAVE_MLOCK
    return mlock(addr, len);
#elif defined(WINAPI_DESKTOP)
    return -(VirtualLock(addr, len) == 0);
#else
    errno = ENOSYS;
    return -1;
#endif
}