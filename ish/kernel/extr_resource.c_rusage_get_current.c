#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_info_t ;
struct TYPE_13__ {int /*<<< orphan*/  microseconds; int /*<<< orphan*/  seconds; } ;
struct TYPE_11__ {int /*<<< orphan*/  microseconds; int /*<<< orphan*/  seconds; } ;
struct TYPE_14__ {TYPE_6__ system_time; TYPE_4__ user_time; } ;
typedef  TYPE_7__ thread_basic_info_data_t ;
struct TYPE_12__ {int /*<<< orphan*/  usec; int /*<<< orphan*/  sec; } ;
struct TYPE_10__ {int /*<<< orphan*/  usec; int /*<<< orphan*/  sec; } ;
struct rusage_ {TYPE_5__ stime; TYPE_3__ utime; } ;
struct TYPE_9__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  RUSAGE_THREAD ; 
 int /*<<< orphan*/  THREAD_BASIC_INFO ; 
 int /*<<< orphan*/  THREAD_BASIC_INFO_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 int getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  mach_thread_self () ; 
 int /*<<< orphan*/  thread_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct rusage_ rusage_get_current() {
    // only the time fields are currently implemented
    struct rusage_ rusage;
#if __linux__
    struct rusage usage;
    int err = getrusage(RUSAGE_THREAD, &usage);
    assert(err == 0);
    rusage.utime.sec = usage.ru_utime.tv_sec;
    rusage.utime.usec = usage.ru_utime.tv_usec;
    rusage.stime.sec = usage.ru_stime.tv_sec;
    rusage.stime.usec = usage.ru_stime.tv_usec;
#elif __APPLE__
    thread_basic_info_data_t info;
    mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
    thread_info(mach_thread_self(), THREAD_BASIC_INFO, (thread_info_t) &info, &count);
    rusage.utime.sec = info.user_time.seconds;
    rusage.utime.usec = info.user_time.microseconds;
    rusage.stime.sec = info.system_time.seconds;
    rusage.stime.usec = info.system_time.microseconds;
#endif
    return rusage;
}