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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {int /*<<< orphan*/  methodState; int /*<<< orphan*/  ignore; } ;
struct eap_gpsk_data {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 scalar_t__ GPSK_1 ; 
 int /*<<< orphan*/  GPSK_3 ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * eap_gpsk_process_csuite_list (struct eap_sm*,struct eap_gpsk_data*,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * eap_gpsk_process_id_server (struct eap_gpsk_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * eap_gpsk_process_rand_server (struct eap_gpsk_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 struct wpabuf* eap_gpsk_send_gpsk_2 (struct eap_gpsk_data*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  eap_gpsk_state (struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_gpsk_process_gpsk_1(struct eap_sm *sm,
					       struct eap_gpsk_data *data,
					       struct eap_method_ret *ret,
					       u8 identifier,
					       const u8 *payload,
					       size_t payload_len)
{
	size_t csuite_list_len;
	const u8 *csuite_list, *pos, *end;
	struct wpabuf *resp;

	if (data->state != GPSK_1) {
		ret->ignore = TRUE;
		return NULL;
	}

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Received Request/GPSK-1");

	end = payload + payload_len;

	pos = eap_gpsk_process_id_server(data, payload, end);
	pos = eap_gpsk_process_rand_server(data, pos, end);
	pos = eap_gpsk_process_csuite_list(sm, data, &csuite_list,
					   &csuite_list_len, pos, end);
	if (pos == NULL) {
		ret->methodState = METHOD_DONE;
		eap_gpsk_state(data, FAILURE);
		return NULL;
	}

	resp = eap_gpsk_send_gpsk_2(data, identifier,
				    csuite_list, csuite_list_len);
	if (resp == NULL)
		return NULL;

	eap_gpsk_state(data, GPSK_3);

	return resp;
}