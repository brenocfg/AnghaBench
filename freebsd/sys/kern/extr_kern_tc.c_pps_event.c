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
typedef  int uint64_t ;
typedef  int u_int ;
struct timespec {scalar_t__ tv_nsec; int tv_sec; } ;
struct TYPE_10__ {int /*<<< orphan*/  clear_sequence; struct timespec clear_timestamp; scalar_t__ clear_ffcount; int /*<<< orphan*/  assert_sequence; struct timespec assert_timestamp; scalar_t__ assert_ffcount; } ;
struct TYPE_9__ {int /*<<< orphan*/  clear_sequence; struct timespec clear_timestamp; int /*<<< orphan*/  assert_sequence; struct timespec assert_timestamp; } ;
struct TYPE_8__ {int mode; struct timespec clear_offset; struct timespec assert_offset; } ;
struct pps_state {scalar_t__ capgen; int kcmode; int* ppscount; int capcount; TYPE_5__* capth; TYPE_7__* capffth; TYPE_4__* ppstc; TYPE_3__ ppsinfo_ffc; TYPE_2__ ppsinfo; TYPE_1__ ppsparam; } ;
struct bintime {scalar_t__ frac; scalar_t__ sec; } ;
typedef  int /*<<< orphan*/  pps_seq_t ;
typedef  scalar_t__ ffcounter ;
struct TYPE_13__ {int /*<<< orphan*/  period; } ;
struct TYPE_14__ {struct bintime tick_time; TYPE_6__ cest; scalar_t__ tick_ffcount; } ;
struct TYPE_12__ {scalar_t__ th_generation; int th_offset_count; int th_scale; TYPE_4__* th_counter; struct bintime th_bintime; } ;
struct TYPE_11__ {int tc_counter_mask; int tc_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int PPS_CAPTUREASSERT ; 
 int PPS_CAPTURECLEAR ; 
 int PPS_OFFSETASSERT ; 
 int PPS_OFFSETCLEAR ; 
 scalar_t__ atomic_load_acq_int (scalar_t__*) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 int /*<<< orphan*/  bintime2timespec (struct bintime*,struct timespec*) ; 
 int /*<<< orphan*/  bintime_add (struct bintime*,struct bintime*) ; 
 int /*<<< orphan*/  bintime_addx (struct bintime*,int) ; 
 int /*<<< orphan*/  ffclock_convert_delta (int,int /*<<< orphan*/ ,struct bintime*) ; 
 int /*<<< orphan*/  hardpps (struct timespec*,scalar_t__) ; 
 int /*<<< orphan*/  timespecadd (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  wakeup (struct pps_state*) ; 

void
pps_event(struct pps_state *pps, int event)
{
	struct bintime bt;
	struct timespec ts, *tsp, *osp;
	u_int tcount, *pcount;
	int foff;
	pps_seq_t *pseq;
#ifdef FFCLOCK
	struct timespec *tsp_ffc;
	pps_seq_t *pseq_ffc;
	ffcounter *ffcount;
#endif
#ifdef PPS_SYNC
	int fhard;
#endif

	KASSERT(pps != NULL, ("NULL pps pointer in pps_event"));
	/* Nothing to do if not currently set to capture this event type. */
	if ((event & pps->ppsparam.mode) == 0)
		return;
	/* If the timecounter was wound up underneath us, bail out. */
	if (pps->capgen == 0 || pps->capgen !=
	    atomic_load_acq_int(&pps->capth->th_generation))
		return;

	/* Things would be easier with arrays. */
	if (event == PPS_CAPTUREASSERT) {
		tsp = &pps->ppsinfo.assert_timestamp;
		osp = &pps->ppsparam.assert_offset;
		foff = pps->ppsparam.mode & PPS_OFFSETASSERT;
#ifdef PPS_SYNC
		fhard = pps->kcmode & PPS_CAPTUREASSERT;
#endif
		pcount = &pps->ppscount[0];
		pseq = &pps->ppsinfo.assert_sequence;
#ifdef FFCLOCK
		ffcount = &pps->ppsinfo_ffc.assert_ffcount;
		tsp_ffc = &pps->ppsinfo_ffc.assert_timestamp;
		pseq_ffc = &pps->ppsinfo_ffc.assert_sequence;
#endif
	} else {
		tsp = &pps->ppsinfo.clear_timestamp;
		osp = &pps->ppsparam.clear_offset;
		foff = pps->ppsparam.mode & PPS_OFFSETCLEAR;
#ifdef PPS_SYNC
		fhard = pps->kcmode & PPS_CAPTURECLEAR;
#endif
		pcount = &pps->ppscount[1];
		pseq = &pps->ppsinfo.clear_sequence;
#ifdef FFCLOCK
		ffcount = &pps->ppsinfo_ffc.clear_ffcount;
		tsp_ffc = &pps->ppsinfo_ffc.clear_timestamp;
		pseq_ffc = &pps->ppsinfo_ffc.clear_sequence;
#endif
	}

	/*
	 * If the timecounter changed, we cannot compare the count values, so
	 * we have to drop the rest of the PPS-stuff until the next event.
	 */
	if (pps->ppstc != pps->capth->th_counter) {
		pps->ppstc = pps->capth->th_counter;
		*pcount = pps->capcount;
		pps->ppscount[2] = pps->capcount;
		return;
	}

	/* Convert the count to a timespec. */
	tcount = pps->capcount - pps->capth->th_offset_count;
	tcount &= pps->capth->th_counter->tc_counter_mask;
	bt = pps->capth->th_bintime;
	bintime_addx(&bt, pps->capth->th_scale * tcount);
	bintime2timespec(&bt, &ts);

	/* If the timecounter was wound up underneath us, bail out. */
	atomic_thread_fence_acq();
	if (pps->capgen != pps->capth->th_generation)
		return;

	*pcount = pps->capcount;
	(*pseq)++;
	*tsp = ts;

	if (foff) {
		timespecadd(tsp, osp, tsp);
		if (tsp->tv_nsec < 0) {
			tsp->tv_nsec += 1000000000;
			tsp->tv_sec -= 1;
		}
	}

#ifdef FFCLOCK
	*ffcount = pps->capffth->tick_ffcount + tcount;
	bt = pps->capffth->tick_time;
	ffclock_convert_delta(tcount, pps->capffth->cest.period, &bt);
	bintime_add(&bt, &pps->capffth->tick_time);
	bintime2timespec(&bt, &ts);
	(*pseq_ffc)++;
	*tsp_ffc = ts;
#endif

#ifdef PPS_SYNC
	if (fhard) {
		uint64_t scale;

		/*
		 * Feed the NTP PLL/FLL.
		 * The FLL wants to know how many (hardware) nanoseconds
		 * elapsed since the previous event.
		 */
		tcount = pps->capcount - pps->ppscount[2];
		pps->ppscount[2] = pps->capcount;
		tcount &= pps->capth->th_counter->tc_counter_mask;
		scale = (uint64_t)1 << 63;
		scale /= pps->capth->th_counter->tc_frequency;
		scale *= 2;
		bt.sec = 0;
		bt.frac = 0;
		bintime_addx(&bt, scale * tcount);
		bintime2timespec(&bt, &ts);
		hardpps(tsp, ts.tv_nsec + 1000000000 * ts.tv_sec);
	}
#endif

	/* Wakeup anyone sleeping in pps_fetch().  */
	wakeup(pps);
}