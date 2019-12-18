#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_6__ {int /*<<< orphan*/  current_mode; int /*<<< orphan*/  clear_sequence; int /*<<< orphan*/  assert_sequence; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
struct pps_state {int flags; TYPE_3__ ppsinfo; TYPE_2__ ppsparam; int /*<<< orphan*/ * driver_mtx; } ;
struct TYPE_4__ {int tv_sec; int tv_nsec; } ;
struct pps_fetch_args {scalar_t__ tsformat; TYPE_3__ pps_info_buf; TYPE_1__ timeout; } ;
typedef  scalar_t__ pps_seq_t ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  PCATCH ; 
 int PPSFLAG_MTX_SPIN ; 
 scalar_t__ PPS_TSFMT_TSPEC ; 
 scalar_t__ abi_aware (struct pps_state*,int) ; 
 scalar_t__ atomic_load_int (int /*<<< orphan*/ *) ; 
 int msleep (struct pps_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int msleep_spin (struct pps_state*,int /*<<< orphan*/ *,char*,int) ; 
 int tsleep (struct pps_state*,int /*<<< orphan*/ ,char*,int) ; 
 int tvtohz (struct timeval*) ; 

__attribute__((used)) static int
pps_fetch(struct pps_fetch_args *fapi, struct pps_state *pps)
{
	int err, timo;
	pps_seq_t aseq, cseq;
	struct timeval tv;

	if (fapi->tsformat && fapi->tsformat != PPS_TSFMT_TSPEC)
		return (EINVAL);

	/*
	 * If no timeout is requested, immediately return whatever values were
	 * most recently captured.  If timeout seconds is -1, that's a request
	 * to block without a timeout.  WITNESS won't let us sleep forever
	 * without a lock (we really don't need a lock), so just repeatedly
	 * sleep a long time.
	 */
	if (fapi->timeout.tv_sec || fapi->timeout.tv_nsec) {
		if (fapi->timeout.tv_sec == -1)
			timo = 0x7fffffff;
		else {
			tv.tv_sec = fapi->timeout.tv_sec;
			tv.tv_usec = fapi->timeout.tv_nsec / 1000;
			timo = tvtohz(&tv);
		}
		aseq = atomic_load_int(&pps->ppsinfo.assert_sequence);
		cseq = atomic_load_int(&pps->ppsinfo.clear_sequence);
		while (aseq == atomic_load_int(&pps->ppsinfo.assert_sequence) &&
		    cseq == atomic_load_int(&pps->ppsinfo.clear_sequence)) {
			if (abi_aware(pps, 1) && pps->driver_mtx != NULL) {
				if (pps->flags & PPSFLAG_MTX_SPIN) {
					err = msleep_spin(pps, pps->driver_mtx,
					    "ppsfch", timo);
				} else {
					err = msleep(pps, pps->driver_mtx, PCATCH,
					    "ppsfch", timo);
				}
			} else {
				err = tsleep(pps, PCATCH, "ppsfch", timo);
			}
			if (err == EWOULDBLOCK) {
				if (fapi->timeout.tv_sec == -1) {
					continue;
				} else {
					return (ETIMEDOUT);
				}
			} else if (err != 0) {
				return (err);
			}
		}
	}

	pps->ppsinfo.current_mode = pps->ppsparam.mode;
	fapi->pps_info_buf = pps->ppsinfo;

	return (0);
}