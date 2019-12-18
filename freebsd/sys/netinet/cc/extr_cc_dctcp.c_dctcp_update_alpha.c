#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct dctcp {int alpha; int bytes_total; int /*<<< orphan*/  save_sndnxt; scalar_t__ bytes_ecn; } ;
struct cc_var {struct dctcp* cc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int DCTCP_SHIFT ; 
 int /*<<< orphan*/  MAX_ALPHA_VALUE ; 
 int V_dctcp_shift_g ; 
 int max (int,int) ; 
 int /*<<< orphan*/  snd_nxt ; 
 int ulmin (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dctcp_update_alpha(struct cc_var *ccv)
{
	struct dctcp *dctcp_data;
	int alpha_prev;

	dctcp_data = ccv->cc_data;
	alpha_prev = dctcp_data->alpha;
	dctcp_data->bytes_total = max(dctcp_data->bytes_total, 1);

	/*
	 * Update alpha: alpha = (1 - g) * alpha + g * M.
	 * Here:
	 * g is weight factor
	 *	recommaded to be set to 1/16
	 *	small g = slow convergence between competitive DCTCP flows
	 *	large g = impacts low utilization of bandwidth at switches
	 * M is fraction of marked segments in last RTT
	 *	updated every RTT
	 * Alpha must be round to 0 - MAX_ALPHA_VALUE.
	 */
	dctcp_data->alpha = ulmin(alpha_prev - (alpha_prev >> V_dctcp_shift_g) +
	    ((uint64_t)dctcp_data->bytes_ecn << (DCTCP_SHIFT - V_dctcp_shift_g)) /
	    dctcp_data->bytes_total, MAX_ALPHA_VALUE);

	/* Initialize internal parameters for next alpha calculation */
	dctcp_data->bytes_ecn = 0;
	dctcp_data->bytes_total = 0;
	dctcp_data->save_sndnxt = CCV(ccv, snd_nxt);
}