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
struct timespec_ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  clockid_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
#define  CLOCK_MONOTONIC_ 129 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
#define  CLOCK_REALTIME_ 128 
 int /*<<< orphan*/  STRACE (char*,int,int /*<<< orphan*/ ) ; 
 int _EFAULT ; 
 int _EINVAL ; 
 int clock_getres (int /*<<< orphan*/ ,struct timespec*) ; 
 int errno_map () ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct timespec_) ; 

dword_t sys_clock_getres(dword_t clock, addr_t res_addr) {
    STRACE("clock_getres(%d, %#x)", clock, res_addr);
    clockid_t clock_id;
    switch (clock) {
        case CLOCK_REALTIME_: clock_id = CLOCK_REALTIME; break;
        case CLOCK_MONOTONIC_: clock_id = CLOCK_MONOTONIC; break;
        default: return _EINVAL;
    }

    struct timespec res;
    int err = clock_getres(clock_id, &res);
    if (err < 0)
        return errno_map();
    struct timespec_ t;
    t.sec = res.tv_sec;
    t.nsec = res.tv_nsec;
    if (user_put(res_addr, t))
        return _EFAULT;
    return 0;
}