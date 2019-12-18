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
struct timeval_ {int dummy; } ;
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD_ ; 
 int /*<<< orphan*/  _EFAULT ; 
 struct timespec convert_timeval (struct timeval_) ; 
 int /*<<< orphan*/  sys_utime_common (int /*<<< orphan*/ ,scalar_t__,struct timespec,struct timespec,int /*<<< orphan*/ ) ; 
 struct timespec timespec_now () ; 
 scalar_t__ user_get (scalar_t__,struct timeval_*) ; 

dword_t sys_utimes(addr_t path_addr, addr_t times_addr) {
    struct timespec atime;
    struct timespec mtime;
    if (times_addr == 0) {
        atime = mtime = timespec_now();
    } else {
        struct timeval_ times[2];
        if (user_get(times_addr, times))
            return _EFAULT;
        atime = convert_timeval(times[0]);
        mtime = convert_timeval(times[1]);
    }
    return sys_utime_common(AT_FDCWD_, path_addr, atime, mtime, 0);
}