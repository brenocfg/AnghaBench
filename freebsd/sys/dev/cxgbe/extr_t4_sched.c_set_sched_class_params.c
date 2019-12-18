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
struct tx_cl_rl_params {scalar_t__ refcount; int flags; int ratemode; int rateunit; int mode; size_t maxrate; size_t pktsize; } ;
struct t4_sched_class_params {scalar_t__ level; scalar_t__ mode; size_t channel; size_t minrate; size_t maxrate; scalar_t__ rateunit; scalar_t__ ratemode; size_t weight; size_t cl; size_t pktsize; } ;
struct port_info {size_t tx_chan; TYPE_4__* sched_params; TYPE_3__* vi; } ;
struct adapter {size_t* chan_map; int /*<<< orphan*/  tc_lock; TYPE_1__* chip_params; struct port_info** port; } ;
struct TYPE_8__ {struct tx_cl_rl_params* cl_rl; } ;
struct TYPE_7__ {TYPE_2__* ifp; } ;
struct TYPE_6__ {int if_mtu; } ;
struct TYPE_5__ {int nchan; int nsched_cls; } ;

/* Variables and functions */
 int CLRL_ASYNC ; 
 int CLRL_ERR ; 
 int CLRL_SYNC ; 
 int CLRL_USER ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 int ERANGE ; 
 int FW_SCHED_PARAMS_LEVEL_CH_RL ; 
 int FW_SCHED_PARAMS_LEVEL_CL_RL ; 
 int FW_SCHED_PARAMS_LEVEL_CL_WRR ; 
 int FW_SCHED_PARAMS_MODE_CLASS ; 
 int FW_SCHED_PARAMS_MODE_FLOW ; 
 int FW_SCHED_PARAMS_RATE_ABS ; 
 int FW_SCHED_PARAMS_RATE_REL ; 
 int FW_SCHED_PARAMS_UNIT_BITRATE ; 
 int FW_SCHED_PARAMS_UNIT_PKTRATE ; 
 int /*<<< orphan*/  FW_SCHED_TYPE_PKTSCHED ; 
 int HOLD_LOCK ; 
 int INTR_OK ; 
 int /*<<< orphan*/  LOCK_HELD ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ SCHED_CLASS_LEVEL_CH_RL ; 
 scalar_t__ SCHED_CLASS_LEVEL_CL_RL ; 
 scalar_t__ SCHED_CLASS_LEVEL_CL_WRR ; 
 scalar_t__ SCHED_CLASS_MODE_CLASS ; 
 scalar_t__ SCHED_CLASS_MODE_FLOW ; 
 scalar_t__ SCHED_CLASS_RATEMODE_ABS ; 
 scalar_t__ SCHED_CLASS_RATEMODE_REL ; 
 scalar_t__ SCHED_CLASS_RATEUNIT_BITS ; 
 scalar_t__ SCHED_CLASS_RATEUNIT_PKTS ; 
 int SLEEP_OK ; 
 int begin_synchronized_op (struct adapter*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_range (size_t,int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int port_top_speed (struct port_info*) ; 
 int t4_sched_params (struct adapter*,int /*<<< orphan*/ ,int,int,int,int,size_t,size_t,size_t,size_t,size_t,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
set_sched_class_params(struct adapter *sc, struct t4_sched_class_params *p,
    int sleep_ok)
{
	int rc, top_speed, fw_level, fw_mode, fw_rateunit, fw_ratemode;
	struct port_info *pi;
	struct tx_cl_rl_params *tc, old;
	bool check_pktsize = false;

	if (p->level == SCHED_CLASS_LEVEL_CL_RL)
		fw_level = FW_SCHED_PARAMS_LEVEL_CL_RL;
	else if (p->level == SCHED_CLASS_LEVEL_CL_WRR)
		fw_level = FW_SCHED_PARAMS_LEVEL_CL_WRR;
	else if (p->level == SCHED_CLASS_LEVEL_CH_RL)
		fw_level = FW_SCHED_PARAMS_LEVEL_CH_RL;
	else
		return (EINVAL);

	if (p->level == SCHED_CLASS_LEVEL_CL_RL) {
		if (p->mode == SCHED_CLASS_MODE_CLASS)
			fw_mode = FW_SCHED_PARAMS_MODE_CLASS;
		else if (p->mode == SCHED_CLASS_MODE_FLOW) {
			check_pktsize = true;
			fw_mode = FW_SCHED_PARAMS_MODE_FLOW;
		} else
			return (EINVAL);
	} else
		fw_mode = 0;

	/* Valid channel must always be provided. */
	if (p->channel < 0)
		return (EINVAL);
	if (!in_range(p->channel, 0, sc->chip_params->nchan - 1))
		return (ERANGE);

	pi = sc->port[sc->chan_map[p->channel]];
	if (pi == NULL)
		return (ENXIO);
	MPASS(pi->tx_chan == p->channel);
	top_speed = port_top_speed(pi) * 1000000; /* Gbps -> Kbps */

	if (p->level == SCHED_CLASS_LEVEL_CL_RL ||
	    p->level == SCHED_CLASS_LEVEL_CH_RL) {
		/*
		 * Valid rate (mode, unit and values) must be provided.
		 */

		if (p->minrate < 0)
			p->minrate = 0;
		if (p->maxrate < 0)
			return (EINVAL);

		if (p->rateunit == SCHED_CLASS_RATEUNIT_BITS) {
			fw_rateunit = FW_SCHED_PARAMS_UNIT_BITRATE;
			/* ratemode could be relative (%) or absolute. */
			if (p->ratemode == SCHED_CLASS_RATEMODE_REL) {
				fw_ratemode = FW_SCHED_PARAMS_RATE_REL;
				/* maxrate is % of port bandwidth. */
				if (!in_range(p->minrate, 0, 100) ||
				    !in_range(p->maxrate, 0, 100)) {
					return (ERANGE);
				}
			} else if (p->ratemode == SCHED_CLASS_RATEMODE_ABS) {
				fw_ratemode = FW_SCHED_PARAMS_RATE_ABS;
				/* maxrate is absolute value in kbps. */
				if (!in_range(p->minrate, 0, top_speed) ||
				    !in_range(p->maxrate, 0, top_speed)) {
					return (ERANGE);
				}
			} else
				return (EINVAL);
		} else if (p->rateunit == SCHED_CLASS_RATEUNIT_PKTS) {
			/* maxrate is the absolute value in pps. */
			check_pktsize = true;
			fw_rateunit = FW_SCHED_PARAMS_UNIT_PKTRATE;
		} else
			return (EINVAL);
	} else {
		MPASS(p->level == SCHED_CLASS_LEVEL_CL_WRR);

		/*
		 * Valid weight must be provided.
		 */
		if (p->weight < 0)
		       return (EINVAL);
		if (!in_range(p->weight, 1, 99))
			return (ERANGE);

		fw_rateunit = 0;
		fw_ratemode = 0;
	}

	if (p->level == SCHED_CLASS_LEVEL_CL_RL ||
	    p->level == SCHED_CLASS_LEVEL_CL_WRR) {
		/*
		 * Valid scheduling class must be provided.
		 */
		if (p->cl < 0)
			return (EINVAL);
		if (!in_range(p->cl, 0, sc->chip_params->nsched_cls - 1))
			return (ERANGE);
	}

	if (check_pktsize) {
		if (p->pktsize < 0)
			return (EINVAL);
		if (!in_range(p->pktsize, 64, pi->vi[0].ifp->if_mtu))
			return (ERANGE);
	}

	if (p->level == SCHED_CLASS_LEVEL_CL_RL) {
		tc = &pi->sched_params->cl_rl[p->cl];
		mtx_lock(&sc->tc_lock);
		if (tc->refcount > 0 || tc->flags & (CLRL_SYNC | CLRL_ASYNC))
			rc = EBUSY;
		else {
			tc->flags |= CLRL_SYNC | CLRL_USER;
			tc->ratemode = fw_ratemode;
			tc->rateunit = fw_rateunit;
			tc->mode = fw_mode;
			tc->maxrate = p->maxrate;
			tc->pktsize = p->pktsize;
			rc = 0;
			old= *tc;
		}
		mtx_unlock(&sc->tc_lock);
		if (rc != 0)
			return (rc);
	}

	rc = begin_synchronized_op(sc, NULL,
	    sleep_ok ? (SLEEP_OK | INTR_OK) : HOLD_LOCK, "t4sscp");
	if (rc != 0) {
		if (p->level == SCHED_CLASS_LEVEL_CL_RL) {
			mtx_lock(&sc->tc_lock);
			*tc = old;
			mtx_unlock(&sc->tc_lock);
		}
		return (rc);
	}
	rc = -t4_sched_params(sc, FW_SCHED_TYPE_PKTSCHED, fw_level, fw_mode,
	    fw_rateunit, fw_ratemode, p->channel, p->cl, p->minrate, p->maxrate,
	    p->weight, p->pktsize, 0, sleep_ok);
	end_synchronized_op(sc, sleep_ok ? 0 : LOCK_HELD);

	if (p->level == SCHED_CLASS_LEVEL_CL_RL) {
		mtx_lock(&sc->tc_lock);
		MPASS(tc->flags & CLRL_SYNC);
		MPASS(tc->flags & CLRL_USER);
		MPASS(tc->refcount == 0);

		tc->flags &= ~CLRL_SYNC;
		if (rc == 0)
			tc->flags &= ~CLRL_ERR;
		else
			tc->flags |= CLRL_ERR;
		mtx_unlock(&sc->tc_lock);
	}

	return (rc);
}