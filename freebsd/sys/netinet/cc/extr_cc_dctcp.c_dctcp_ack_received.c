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
typedef  scalar_t__ uint16_t ;
struct dctcp {int bytes_total; int ece_prev; int bytes_ecn; int /*<<< orphan*/  save_sndnxt; scalar_t__ ece_curr; } ;
struct cc_var {int bytes_this_ack; int /*<<< orphan*/  curack; struct dctcp* cc_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack_received ) (struct cc_var*,scalar_t__) ;} ;

/* Variables and functions */
 int CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 scalar_t__ CC_ACK ; 
 scalar_t__ CC_DUPACK ; 
 int /*<<< orphan*/  ENTER_CONGRECOVERY (int) ; 
 int /*<<< orphan*/  EXIT_CONGRECOVERY (int) ; 
 scalar_t__ IN_CONGRECOVERY (int) ; 
 scalar_t__ IN_FASTRECOVERY (int) ; 
 scalar_t__ SEQ_GEQ (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TF_ECN_PERMIT ; 
 int /*<<< orphan*/  dctcp_update_alpha (struct cc_var*) ; 
 int min (int,int) ; 
 TYPE_1__ newreno_cc_algo ; 
 int /*<<< orphan*/  snd_recover ; 
 int /*<<< orphan*/  stub1 (struct cc_var*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct cc_var*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct cc_var*,scalar_t__) ; 
 int /*<<< orphan*/  t_flags ; 
 int /*<<< orphan*/  t_maxseg ; 

__attribute__((used)) static void
dctcp_ack_received(struct cc_var *ccv, uint16_t type)
{
	struct dctcp *dctcp_data;
	int bytes_acked = 0;

	dctcp_data = ccv->cc_data;

	if (CCV(ccv, t_flags) & TF_ECN_PERMIT) {
		/*
		 * DCTCP doesn't treat receipt of ECN marked packet as a
		 * congestion event. Thus, DCTCP always executes the ACK
		 * processing out of congestion recovery.
		 */
		if (IN_CONGRECOVERY(CCV(ccv, t_flags))) {
			EXIT_CONGRECOVERY(CCV(ccv, t_flags));
			newreno_cc_algo.ack_received(ccv, type);
			ENTER_CONGRECOVERY(CCV(ccv, t_flags));
		} else
			newreno_cc_algo.ack_received(ccv, type);

		if (type == CC_DUPACK)
			bytes_acked = min(ccv->bytes_this_ack, CCV(ccv, t_maxseg));

		if (type == CC_ACK)
			bytes_acked = ccv->bytes_this_ack;

		/* Update total bytes. */
		dctcp_data->bytes_total += bytes_acked;

		/* Update total marked bytes. */
		if (dctcp_data->ece_curr) {
			//XXRMS: For fluid-model DCTCP, update
			//cwnd here during for RTT fairness
			if (!dctcp_data->ece_prev
			    && bytes_acked > CCV(ccv, t_maxseg)) {
				dctcp_data->bytes_ecn +=
				    (bytes_acked - CCV(ccv, t_maxseg));
			} else
				dctcp_data->bytes_ecn += bytes_acked;
			dctcp_data->ece_prev = 1;
		} else {
			if (dctcp_data->ece_prev
			    && bytes_acked > CCV(ccv, t_maxseg))
				dctcp_data->bytes_ecn += CCV(ccv, t_maxseg);
			dctcp_data->ece_prev = 0;
		}
		dctcp_data->ece_curr = 0;

		/*
		 * Update the fraction of marked bytes at the end of
		 * current window size.
		 */
		if ((IN_FASTRECOVERY(CCV(ccv, t_flags)) &&
		    SEQ_GEQ(ccv->curack, CCV(ccv, snd_recover))) ||
		    (!IN_FASTRECOVERY(CCV(ccv, t_flags)) &&
		    SEQ_GT(ccv->curack, dctcp_data->save_sndnxt)))
			dctcp_update_alpha(ccv);
	} else
		newreno_cc_algo.ack_received(ccv, type);
}