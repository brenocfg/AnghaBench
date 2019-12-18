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
struct tncc_data {struct tnc_if_imc* imc; } ;
struct tnc_if_imc {struct tnc_if_imc* next; } ;
typedef  enum tncc_process_res { ____Placeholder_tncc_process_res } tncc_process_res ;
typedef  int /*<<< orphan*/  TNC_ConnectionState ;

/* Variables and functions */
#define  TNCCS_RECOMMENDATION_ALLOW 130 
#define  TNCCS_RECOMMENDATION_ISOLATE 129 
#define  TNCCS_RECOMMENDATION_NONE 128 
 int /*<<< orphan*/  TNC_CONNECTION_STATE_ACCESS_ALLOWED ; 
 int /*<<< orphan*/  TNC_CONNECTION_STATE_ACCESS_ISOLATED ; 
 int /*<<< orphan*/  TNC_CONNECTION_STATE_ACCESS_NONE ; 
 int /*<<< orphan*/  tncc_imc_notify_connection_change (struct tnc_if_imc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tncc_notify_recommendation(struct tncc_data *tncc,
				       enum tncc_process_res res)
{
	TNC_ConnectionState state;
	struct tnc_if_imc *imc;

	switch (res) {
	case TNCCS_RECOMMENDATION_ALLOW:
		state = TNC_CONNECTION_STATE_ACCESS_ALLOWED;
		break;
	case TNCCS_RECOMMENDATION_NONE:
		state = TNC_CONNECTION_STATE_ACCESS_NONE;
		break;
	case TNCCS_RECOMMENDATION_ISOLATE:
		state = TNC_CONNECTION_STATE_ACCESS_ISOLATED;
		break;
	default:
		state = TNC_CONNECTION_STATE_ACCESS_NONE;
		break;
	}

	for (imc = tncc->imc; imc; imc = imc->next)
		tncc_imc_notify_connection_change(imc, state);
}