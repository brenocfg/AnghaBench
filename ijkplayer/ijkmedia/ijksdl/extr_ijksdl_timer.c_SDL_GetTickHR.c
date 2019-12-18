#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int Uint64 ;
struct TYPE_3__ {int numer; int denom; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_COARSE ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC_HR ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int g_is_mach_base_info_inited ; 
 TYPE_1__ g_mach_base_info ; 
 scalar_t__ g_mach_base_info_ret ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int mach_absolute_time () ; 
 scalar_t__ mach_timebase_info (TYPE_1__*) ; 

Uint64 SDL_GetTickHR(void)
{
    Uint64 clock;
#if defined(__ANDROID__)
    struct timespec now;
#ifdef CLOCK_MONOTONIC_COARSE
    clock_gettime(CLOCK_MONOTONIC_COARSE, &now);
#else
    clock_gettime(CLOCK_MONOTONIC_HR, &now);
#endif
    clock = now.tv_sec * 1000 + now.tv_nsec / 1000000;
#elif defined(__APPLE__)
    if (!g_is_mach_base_info_inited) {
        g_mach_base_info_ret = mach_timebase_info(&g_mach_base_info);
        g_is_mach_base_info_inited = 1;
    }
    if (g_mach_base_info_ret == 0) {
        uint64_t now = mach_absolute_time();
        clock = now * g_mach_base_info.numer / g_mach_base_info.denom / 1000000;
    } else {
        struct timeval now;
        gettimeofday(&now, NULL);
        clock = now.tv_sec  * 1000 + now.tv_usec / 1000;
    }
#endif
    return (clock);
}