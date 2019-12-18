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
typedef  int u_long ;
struct TYPE_7__ {int /*<<< orphan*/  clear_timestamp; int /*<<< orphan*/  assert_timestamp; } ;
struct TYPE_8__ {int mode; int /*<<< orphan*/  api_version; } ;
struct TYPE_6__ {int current_mode; int /*<<< orphan*/  clear_timestamp; int /*<<< orphan*/  assert_timestamp; } ;
struct pps_state {int ppscap; int kcmode; TYPE_3__ ppsinfo; TYPE_4__ ppsparam; TYPE_2__ ppsinfo_ffc; } ;
struct pps_kcbind_args {int edge; int /*<<< orphan*/  kernel_consumer; int /*<<< orphan*/  tsformat; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct pps_fetch_ffc_args {TYPE_2__ pps_info_buf_ffc; TYPE_1__ timeout; int /*<<< orphan*/  tsformat; } ;
struct pps_fetch_args {int dummy; } ;
typedef  TYPE_4__ pps_params_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int KCMODE_ABIFLAG ; 
 int KCMODE_EDGEMASK ; 
 int /*<<< orphan*/  PPS_API_VERS_1 ; 
#define  PPS_IOC_CREATE 137 
#define  PPS_IOC_DESTROY 136 
#define  PPS_IOC_FETCH 135 
#define  PPS_IOC_FETCH_FFCOUNTER 134 
#define  PPS_IOC_GETCAP 133 
#define  PPS_IOC_GETPARAMS 132 
#define  PPS_IOC_KCBIND 131 
#define  PPS_IOC_SETPARAMS 130 
 int /*<<< orphan*/  PPS_KC_HARDPPS ; 
#define  PPS_TSCLK_FBCK 129 
#define  PPS_TSCLK_FFWD 128 
 int PPS_TSCLK_MASK ; 
 int /*<<< orphan*/  PPS_TSFMT_TSPEC ; 
 int pps_fetch (struct pps_fetch_args*,struct pps_state*) ; 

int
pps_ioctl(u_long cmd, caddr_t data, struct pps_state *pps)
{
	pps_params_t *app;
	struct pps_fetch_args *fapi;
#ifdef FFCLOCK
	struct pps_fetch_ffc_args *fapi_ffc;
#endif
#ifdef PPS_SYNC
	struct pps_kcbind_args *kapi;
#endif

	KASSERT(pps != NULL, ("NULL pps pointer in pps_ioctl"));
	switch (cmd) {
	case PPS_IOC_CREATE:
		return (0);
	case PPS_IOC_DESTROY:
		return (0);
	case PPS_IOC_SETPARAMS:
		app = (pps_params_t *)data;
		if (app->mode & ~pps->ppscap)
			return (EINVAL);
#ifdef FFCLOCK
		/* Ensure only a single clock is selected for ffc timestamp. */
		if ((app->mode & PPS_TSCLK_MASK) == PPS_TSCLK_MASK)
			return (EINVAL);
#endif
		pps->ppsparam = *app;
		return (0);
	case PPS_IOC_GETPARAMS:
		app = (pps_params_t *)data;
		*app = pps->ppsparam;
		app->api_version = PPS_API_VERS_1;
		return (0);
	case PPS_IOC_GETCAP:
		*(int*)data = pps->ppscap;
		return (0);
	case PPS_IOC_FETCH:
		fapi = (struct pps_fetch_args *)data;
		return (pps_fetch(fapi, pps));
#ifdef FFCLOCK
	case PPS_IOC_FETCH_FFCOUNTER:
		fapi_ffc = (struct pps_fetch_ffc_args *)data;
		if (fapi_ffc->tsformat && fapi_ffc->tsformat !=
		    PPS_TSFMT_TSPEC)
			return (EINVAL);
		if (fapi_ffc->timeout.tv_sec || fapi_ffc->timeout.tv_nsec)
			return (EOPNOTSUPP);
		pps->ppsinfo_ffc.current_mode = pps->ppsparam.mode;
		fapi_ffc->pps_info_buf_ffc = pps->ppsinfo_ffc;
		/* Overwrite timestamps if feedback clock selected. */
		switch (pps->ppsparam.mode & PPS_TSCLK_MASK) {
		case PPS_TSCLK_FBCK:
			fapi_ffc->pps_info_buf_ffc.assert_timestamp =
			    pps->ppsinfo.assert_timestamp;
			fapi_ffc->pps_info_buf_ffc.clear_timestamp =
			    pps->ppsinfo.clear_timestamp;
			break;
		case PPS_TSCLK_FFWD:
			break;
		default:
			break;
		}
		return (0);
#endif /* FFCLOCK */
	case PPS_IOC_KCBIND:
#ifdef PPS_SYNC
		kapi = (struct pps_kcbind_args *)data;
		/* XXX Only root should be able to do this */
		if (kapi->tsformat && kapi->tsformat != PPS_TSFMT_TSPEC)
			return (EINVAL);
		if (kapi->kernel_consumer != PPS_KC_HARDPPS)
			return (EINVAL);
		if (kapi->edge & ~pps->ppscap)
			return (EINVAL);
		pps->kcmode = (kapi->edge & KCMODE_EDGEMASK) |
		    (pps->kcmode & KCMODE_ABIFLAG);
		return (0);
#else
		return (EOPNOTSUPP);
#endif
	default:
		return (ENOIOCTL);
	}
}