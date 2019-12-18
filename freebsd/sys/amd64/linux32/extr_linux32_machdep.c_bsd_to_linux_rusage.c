#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct rusage {int /*<<< orphan*/  ru_nivcsw; int /*<<< orphan*/  ru_nvcsw; int /*<<< orphan*/  ru_nsignals; int /*<<< orphan*/  ru_msgrcv; int /*<<< orphan*/  ru_msgsnd; int /*<<< orphan*/  ru_oublock; int /*<<< orphan*/  ru_inblock; int /*<<< orphan*/  ru_nswap; int /*<<< orphan*/  ru_majflt; int /*<<< orphan*/  ru_minflt; int /*<<< orphan*/  ru_isrss; int /*<<< orphan*/  ru_idrss; int /*<<< orphan*/  ru_ixrss; int /*<<< orphan*/  ru_maxrss; TYPE_4__ ru_stime; TYPE_2__ ru_utime; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct l_rusage {int /*<<< orphan*/  ru_nivcsw; int /*<<< orphan*/  ru_nvcsw; int /*<<< orphan*/  ru_nsignals; int /*<<< orphan*/  ru_msgrcv; int /*<<< orphan*/  ru_msgsnd; int /*<<< orphan*/  ru_oublock; int /*<<< orphan*/  ru_inblock; int /*<<< orphan*/  ru_nswap; int /*<<< orphan*/  ru_majflt; int /*<<< orphan*/  ru_minflt; int /*<<< orphan*/  ru_isrss; int /*<<< orphan*/  ru_idrss; int /*<<< orphan*/  ru_ixrss; int /*<<< orphan*/  ru_maxrss; TYPE_3__ ru_stime; TYPE_1__ ru_utime; } ;

/* Variables and functions */

__attribute__((used)) static void
bsd_to_linux_rusage(struct rusage *ru, struct l_rusage *lru)
{

	lru->ru_utime.tv_sec = ru->ru_utime.tv_sec;
	lru->ru_utime.tv_usec = ru->ru_utime.tv_usec;
	lru->ru_stime.tv_sec = ru->ru_stime.tv_sec;
	lru->ru_stime.tv_usec = ru->ru_stime.tv_usec;
	lru->ru_maxrss = ru->ru_maxrss;
	lru->ru_ixrss = ru->ru_ixrss;
	lru->ru_idrss = ru->ru_idrss;
	lru->ru_isrss = ru->ru_isrss;
	lru->ru_minflt = ru->ru_minflt;
	lru->ru_majflt = ru->ru_majflt;
	lru->ru_nswap = ru->ru_nswap;
	lru->ru_inblock = ru->ru_inblock;
	lru->ru_oublock = ru->ru_oublock;
	lru->ru_msgsnd = ru->ru_msgsnd;
	lru->ru_msgrcv = ru->ru_msgrcv;
	lru->ru_nsignals = ru->ru_nsignals;
	lru->ru_nvcsw = ru->ru_nvcsw;
	lru->ru_nivcsw = ru->ru_nivcsw;
}