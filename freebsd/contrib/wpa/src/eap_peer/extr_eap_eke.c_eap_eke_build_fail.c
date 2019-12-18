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
typedef  int /*<<< orphan*/  u32 ;
struct wpabuf {int dummy; } ;
struct eap_method_ret {int /*<<< orphan*/  allowNotifications; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; } ;
struct eap_eke_data {int /*<<< orphan*/  sess; int /*<<< orphan*/  dh_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  EAP_EKE_FAILURE ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_eke_build_msg (struct eap_eke_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_eke_session_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_eke_state (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_eke_build_fail(struct eap_eke_data *data,
					  struct eap_method_ret *ret,
					  u8 id, u32 failure_code)
{
	struct wpabuf *resp;

	wpa_printf(MSG_DEBUG, "EAP-EKE: Sending EAP-EKE-Failure/Response - code=0x%x",
		   failure_code);

	resp = eap_eke_build_msg(data, id, 4, EAP_EKE_FAILURE);
	if (resp)
		wpabuf_put_be32(resp, failure_code);

	os_memset(data->dh_priv, 0, sizeof(data->dh_priv));
	eap_eke_session_clean(&data->sess);

	eap_eke_state(data, FAILURE);
	ret->methodState = METHOD_DONE;
	ret->decision = DECISION_FAIL;
	ret->allowNotifications = FALSE;

	return resp;
}