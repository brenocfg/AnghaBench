#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec_ {int nsec; int /*<<< orphan*/  sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int usec; int /*<<< orphan*/  sec; } ;
struct rusage_ {TYPE_1__ utime; } ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  clockid_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
#define  CLOCK_MONOTONIC_ 129 
 int CLOCK_PROCESS_CPUTIME_ID_ ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
#define  CLOCK_REALTIME_ 128 
 int /*<<< orphan*/  STRACE (char*,int,int /*<<< orphan*/ ) ; 
 int _EFAULT ; 
 int _EINVAL ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int errno_map () ; 
 struct rusage_ rusage_get_current () ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct timespec_) ; 

dword_t sys_clock_gettime(dword_t clock, addr_t tp) {
    STRACE("clock_gettime(%d, 0x%x)", clock, tp);

    struct timespec ts;
    if (clock == CLOCK_PROCESS_CPUTIME_ID_) {
        // FIXME this is thread usage, not process usage
        struct rusage_ rusage = rusage_get_current();
        ts.tv_sec = rusage.utime.sec;
        ts.tv_nsec = rusage.utime.usec * 1000;
    } else {
        clockid_t clock_id;
        switch (clock) {
            case CLOCK_REALTIME_: clock_id = CLOCK_REALTIME; break;
            case CLOCK_MONOTONIC_: clock_id = CLOCK_MONOTONIC; break;
            default: return _EINVAL;
        }
        int err = clock_gettime(clock_id, &ts);
        if (err < 0)
            return errno_map();
    }
    struct timespec_ t;
    t.sec = ts.tv_sec;
    t.nsec = ts.tv_nsec;
    if (user_put(tp, t))
        return _EFAULT;
    return 0;
}