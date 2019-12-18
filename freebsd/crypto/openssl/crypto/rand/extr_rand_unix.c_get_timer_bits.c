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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  tb_low; int /*<<< orphan*/  tb_high; } ;
typedef  TYPE_1__ timebasestruct_t ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_TYPE ; 
 scalar_t__ OPENSSL_rdtsc () ; 
 int /*<<< orphan*/  TIMEBASE_SZ ; 
 scalar_t__ TWO32TO64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ gethrtime () ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_wall_time (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t get_timer_bits(void)
{
    uint64_t res = OPENSSL_rdtsc();

    if (res != 0)
        return res;

# if defined(__sun) || defined(__hpux)
    return gethrtime();
# elif defined(_AIX)
    {
        timebasestruct_t t;

        read_wall_time(&t, TIMEBASE_SZ);
        return TWO32TO64(t.tb_high, t.tb_low);
    }
# elif defined(OSSL_POSIX_TIMER_OKAY)
    {
        struct timespec ts;

#  ifdef CLOCK_BOOTTIME
#   define CLOCK_TYPE CLOCK_BOOTTIME
#  elif defined(_POSIX_MONOTONIC_CLOCK)
#   define CLOCK_TYPE CLOCK_MONOTONIC
#  else
#   define CLOCK_TYPE CLOCK_REALTIME
#  endif

        if (clock_gettime(CLOCK_TYPE, &ts) == 0)
            return TWO32TO64(ts.tv_sec, ts.tv_nsec);
    }
# endif
# if defined(__unix__) \
     || (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L)
    {
        struct timeval tv;

        if (gettimeofday(&tv, NULL) == 0)
            return TWO32TO64(tv.tv_sec, tv.tv_usec);
    }
# endif
    return time(NULL);
}