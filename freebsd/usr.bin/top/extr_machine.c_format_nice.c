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
struct TYPE_2__ {int pri_native; int pri_user; int /*<<< orphan*/  pri_class; } ;
struct kinfo_proc {int ki_flag; int ki_nice; TYPE_1__ ki_pri; } ;
typedef  int /*<<< orphan*/  nicebuf ;

/* Variables and functions */
 int NZERO ; 
 int PRI_BASE (int /*<<< orphan*/ ) ; 
#define  PRI_IDLE 131 
#define  PRI_ITHD 130 
 int PRI_MIN_IDLE ; 
 int PRI_MIN_REALTIME ; 
 scalar_t__ PRI_NEED_RR (int /*<<< orphan*/ ) ; 
#define  PRI_REALTIME 129 
#define  PRI_TIMESHARE 128 
 int P_KPROC ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static const char *
format_nice(const struct kinfo_proc *pp)
{
	const char *fifo, *kproc;
	int rtpri;
	static char nicebuf[4 + 1];

	fifo = PRI_NEED_RR(pp->ki_pri.pri_class) ? "" : "F";
	kproc = (pp->ki_flag & P_KPROC) ? "k" : "";
	switch (PRI_BASE(pp->ki_pri.pri_class)) {
	case PRI_ITHD:
		return ("-");
	case PRI_REALTIME:
		/*
		 * XXX: the kernel doesn't tell us the original rtprio and
		 * doesn't really know what it was, so to recover it we
		 * must be more chummy with the implementation than the
		 * implementation is with itself.  pri_user gives a
		 * constant "base" priority, but is only initialized
		 * properly for user threads.  pri_native gives what the
		 * kernel calls the "base" priority, but it isn't constant
		 * since it is changed by priority propagation.  pri_native
		 * also isn't properly initialized for all threads, but it
		 * is properly initialized for kernel realtime and idletime
		 * threads.  Thus we use pri_user for the base priority of
		 * user threads (it is always correct) and pri_native for
		 * the base priority of kernel realtime and idletime threads
		 * (there is nothing better, and it is usually correct).
		 *
		 * The field width and thus the buffer are too small for
		 * values like "kr31F", but such values shouldn't occur,
		 * and if they do then the tailing "F" is not displayed.
		 */
		rtpri = ((pp->ki_flag & P_KPROC) ? pp->ki_pri.pri_native :
		    pp->ki_pri.pri_user) - PRI_MIN_REALTIME;
		snprintf(nicebuf, sizeof(nicebuf), "%sr%d%s",
		    kproc, rtpri, fifo);
		break;
	case PRI_TIMESHARE:
		if (pp->ki_flag & P_KPROC)
			return ("-");
		snprintf(nicebuf, sizeof(nicebuf), "%d", pp->ki_nice - NZERO);
		break;
	case PRI_IDLE:
		/* XXX: as above. */
		rtpri = ((pp->ki_flag & P_KPROC) ? pp->ki_pri.pri_native :
		    pp->ki_pri.pri_user) - PRI_MIN_IDLE;
		snprintf(nicebuf, sizeof(nicebuf), "%si%d%s",
		    kproc, rtpri, fifo);
		break;
	default:
		return ("?");
	}
	return (nicebuf);
}