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
struct tms_ {void* tms_stime; void* tms_cstime; void* tms_utime; void* tms_cutime; } ;
struct rusage_ {int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; } ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  _EFAULT ; 
 void* clock_from_timeval (int /*<<< orphan*/ ) ; 
 struct rusage_ rusage_get_current () ; 
 scalar_t__ user_put (scalar_t__,struct tms_) ; 

dword_t sys_times(addr_t tbuf) {
    STRACE("times(0x%x)", tbuf);
    if (tbuf) {
        struct tms_ tmp;
        struct rusage_ rusage = rusage_get_current();
        tmp.tms_utime = clock_from_timeval(rusage.utime);
        tmp.tms_stime = clock_from_timeval(rusage.stime);
        tmp.tms_cutime = tmp.tms_utime;
        tmp.tms_cstime = tmp.tms_stime;
        if (user_put(tbuf, tmp))
            return _EFAULT;
    }
    return 0;
}