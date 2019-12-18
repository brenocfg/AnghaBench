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
struct icl_pdu {int dummy; } ;
struct cfiscsi_session {int /*<<< orphan*/  cs_login_cv; struct icl_pdu* cs_login_pdu; scalar_t__ cs_login_phase; scalar_t__ cs_waiting_for_ctld; } ;

/* Variables and functions */
 struct cfiscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_pdu_handle (struct icl_pdu*) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 

__attribute__((used)) static void
cfiscsi_receive_callback(struct icl_pdu *request)
{
#ifdef ICL_KERNEL_PROXY
	struct cfiscsi_session *cs;

	cs = PDU_SESSION(request);
	if (cs->cs_waiting_for_ctld || cs->cs_login_phase) {
		if (cs->cs_login_pdu == NULL)
			cs->cs_login_pdu = request;
		else
			icl_pdu_free(request);
		cv_signal(&cs->cs_login_cv);
		return;
	}
#endif

	cfiscsi_pdu_handle(request);
}