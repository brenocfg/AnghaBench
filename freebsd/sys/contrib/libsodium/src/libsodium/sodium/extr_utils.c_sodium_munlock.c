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
 int /*<<< orphan*/  MADV_DODUMP ; 
 scalar_t__ VirtualUnlock (void* const,size_t const) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  madvise (void* const,size_t const,int /*<<< orphan*/ ) ; 
 int munlock (void* const,size_t const) ; 
 int /*<<< orphan*/  sodium_memzero (void* const,size_t const) ; 

int
sodium_munlock(void *const addr, const size_t len)
{
    sodium_memzero(addr, len);
#if defined(MADV_DODUMP) && defined(HAVE_MADVISE)
    (void) madvise(addr, len, MADV_DODUMP);
#endif
#ifdef HAVE_MLOCK
    return munlock(addr, len);
#elif defined(WINAPI_DESKTOP)
    return -(VirtualUnlock(addr, len) == 0);
#else
    errno = ENOSYS;
    return -1;
#endif
}