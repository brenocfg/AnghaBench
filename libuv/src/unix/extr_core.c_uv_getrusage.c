#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_11__ {int /*<<< orphan*/  ru_nivcsw; int /*<<< orphan*/  ru_nvcsw; int /*<<< orphan*/  ru_nsignals; int /*<<< orphan*/  ru_msgrcv; int /*<<< orphan*/  ru_msgsnd; int /*<<< orphan*/  ru_oublock; int /*<<< orphan*/  ru_inblock; int /*<<< orphan*/  ru_nswap; int /*<<< orphan*/  ru_majflt; int /*<<< orphan*/  ru_minflt; int /*<<< orphan*/  ru_isrss; int /*<<< orphan*/  ru_idrss; int /*<<< orphan*/  ru_ixrss; int /*<<< orphan*/  ru_maxrss; TYPE_3__ ru_stime; TYPE_1__ ru_utime; } ;
typedef  TYPE_5__ uv_rusage_t ;
struct TYPE_10__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct rusage {int /*<<< orphan*/  ru_nivcsw; int /*<<< orphan*/  ru_nvcsw; int /*<<< orphan*/  ru_nsignals; int /*<<< orphan*/  ru_msgrcv; int /*<<< orphan*/  ru_msgsnd; int /*<<< orphan*/  ru_oublock; int /*<<< orphan*/  ru_inblock; int /*<<< orphan*/  ru_nswap; int /*<<< orphan*/  ru_majflt; int /*<<< orphan*/  ru_minflt; int /*<<< orphan*/  ru_isrss; int /*<<< orphan*/  ru_idrss; int /*<<< orphan*/  ru_ixrss; int /*<<< orphan*/  ru_maxrss; TYPE_4__ ru_stime; TYPE_2__ ru_utime; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getrusage (int /*<<< orphan*/ ,struct rusage*) ; 

int uv_getrusage(uv_rusage_t* rusage) {
  struct rusage usage;

  if (getrusage(RUSAGE_SELF, &usage))
    return UV__ERR(errno);

  rusage->ru_utime.tv_sec = usage.ru_utime.tv_sec;
  rusage->ru_utime.tv_usec = usage.ru_utime.tv_usec;

  rusage->ru_stime.tv_sec = usage.ru_stime.tv_sec;
  rusage->ru_stime.tv_usec = usage.ru_stime.tv_usec;

#if !defined(__MVS__) && !defined(__HAIKU__)
  rusage->ru_maxrss = usage.ru_maxrss;
  rusage->ru_ixrss = usage.ru_ixrss;
  rusage->ru_idrss = usage.ru_idrss;
  rusage->ru_isrss = usage.ru_isrss;
  rusage->ru_minflt = usage.ru_minflt;
  rusage->ru_majflt = usage.ru_majflt;
  rusage->ru_nswap = usage.ru_nswap;
  rusage->ru_inblock = usage.ru_inblock;
  rusage->ru_oublock = usage.ru_oublock;
  rusage->ru_msgsnd = usage.ru_msgsnd;
  rusage->ru_msgrcv = usage.ru_msgrcv;
  rusage->ru_nsignals = usage.ru_nsignals;
  rusage->ru_nvcsw = usage.ru_nvcsw;
  rusage->ru_nivcsw = usage.ru_nivcsw;
#endif

  return 0;
}