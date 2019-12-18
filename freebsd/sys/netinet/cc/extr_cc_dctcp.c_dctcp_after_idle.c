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
struct dctcp {int save_sndnxt; scalar_t__ num_cong_events; scalar_t__ ece_prev; scalar_t__ ece_curr; int /*<<< orphan*/  alpha; scalar_t__ bytes_total; scalar_t__ bytes_ecn; } ;
struct cc_var {struct dctcp* cc_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* after_idle ) (struct cc_var*) ;} ;

/* Variables and functions */
 int CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int TF_ECN_PERMIT ; 
 int /*<<< orphan*/  V_dctcp_alpha ; 
 TYPE_1__ newreno_cc_algo ; 
 int /*<<< orphan*/  snd_nxt ; 
 int /*<<< orphan*/  stub1 (struct cc_var*) ; 
 int /*<<< orphan*/  t_flags ; 

__attribute__((used)) static void
dctcp_after_idle(struct cc_var *ccv)
{
	struct dctcp *dctcp_data;

	if (CCV(ccv, t_flags) & TF_ECN_PERMIT) {
		dctcp_data = ccv->cc_data;

		/* Initialize internal parameters after idle time */
		dctcp_data->bytes_ecn = 0;
		dctcp_data->bytes_total = 0;
		dctcp_data->save_sndnxt = CCV(ccv, snd_nxt);
		dctcp_data->alpha = V_dctcp_alpha;
		dctcp_data->ece_curr = 0;
		dctcp_data->ece_prev = 0;
		dctcp_data->num_cong_events = 0;
	}

	newreno_cc_algo.after_idle(ccv);
}