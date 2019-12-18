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
struct eap_sm {int dummy; } ;
struct eap_peap_data {scalar_t__ state; scalar_t__ peap_version; int /*<<< orphan*/  tlv_request; } ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ FAILURE_REQ ; 
 scalar_t__ PHASE2_TLV ; 
 scalar_t__ SUCCESS_REQ ; 
 int /*<<< orphan*/  TLV_REQ_SUCCESS ; 
 int /*<<< orphan*/  eap_peap_state (struct eap_peap_data*,scalar_t__) ; 

__attribute__((used)) static void eap_peap_req_success(struct eap_sm *sm,
				 struct eap_peap_data *data)
{
	if (data->state == FAILURE || data->state == FAILURE_REQ) {
		eap_peap_state(data, FAILURE);
		return;
	}

	if (data->peap_version == 0) {
		data->tlv_request = TLV_REQ_SUCCESS;
		eap_peap_state(data, PHASE2_TLV);
	} else {
		eap_peap_state(data, SUCCESS_REQ);
	}
}