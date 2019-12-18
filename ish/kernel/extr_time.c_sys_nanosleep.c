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
typedef  int /*<<< orphan*/  dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _EFAULT ; 
 int /*<<< orphan*/  errno_map () ; 
 scalar_t__ nanosleep (struct timespec*,struct timespec*) ; 
 scalar_t__ user_get (int /*<<< orphan*/ ,struct timespec_) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct timespec_) ; 

dword_t sys_nanosleep(addr_t req_addr, addr_t rem_addr) {
    struct timespec_ req_ts;
    if (user_get(req_addr, req_ts))
        return _EFAULT;
    STRACE("nanosleep({%d, %d}, 0x%x", req_ts.sec, req_ts.nsec, rem_addr);
    struct timespec req;
    req.tv_sec = req_ts.sec;
    req.tv_nsec = req_ts.nsec;
    struct timespec rem;
    if (nanosleep(&req, &rem) < 0)
        return errno_map();
    if (rem_addr != 0) {
        struct timespec_ rem_ts;
        rem_ts.sec = rem.tv_sec;
        rem_ts.nsec = rem.tv_nsec;
        if (user_put(rem_addr, rem_ts))
            return _EFAULT;
    }
    return 0;
}