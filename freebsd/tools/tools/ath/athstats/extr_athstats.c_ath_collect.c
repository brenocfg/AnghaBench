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
struct TYPE_2__ {int ad_out_size; void* ad_out_data; int /*<<< orphan*/  ad_id; } ;
struct athstatfoo_p {int optstats; TYPE_1__ atd; int /*<<< orphan*/  req; } ;
struct _athstats {int /*<<< orphan*/  ani_stats; int /*<<< orphan*/  ani_state; int /*<<< orphan*/  ath; } ;
typedef  void* caddr_t ;

/* Variables and functions */
 int ATHSTATS_ANI ; 
 int /*<<< orphan*/  HAL_DIAG_ANI_CURRENT ; 
 int /*<<< orphan*/  HAL_DIAG_ANI_STATS ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 scalar_t__ ath_driver_req_fetch_diag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ath_driver_req_fetch_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static void
ath_collect(struct athstatfoo_p *wf, struct _athstats *stats)
{

	if (ath_driver_req_fetch_stats(&wf->req, &stats->ath) < 0)
		exit(1);
#ifdef ATH_SUPPORT_ANI
	if (wf->optstats & ATHSTATS_ANI) {

		/* XXX TODO: convert */
		wf->atd.ad_id = HAL_DIAG_ANI_CURRENT; /* HAL_DIAG_ANI_CURRENT */
		wf->atd.ad_out_data = (caddr_t) &stats->ani_state;
		wf->atd.ad_out_size = sizeof(stats->ani_state);
		if (ath_driver_req_fetch_diag(&wf->req, SIOCGATHDIAG,
		    &wf->atd) < 0) {
			wf->optstats &= ~ATHSTATS_ANI;
		}

		/* XXX TODO: convert */
		wf->atd.ad_id = HAL_DIAG_ANI_STATS; /* HAL_DIAG_ANI_STATS */
		wf->atd.ad_out_data = (caddr_t) &stats->ani_stats;
		wf->atd.ad_out_size = sizeof(stats->ani_stats);
		(void) ath_driver_req_fetch_diag(&wf->req, SIOCGATHDIAG,
		    &wf->atd);
	}
#endif /* ATH_SUPPORT_ANI */
}