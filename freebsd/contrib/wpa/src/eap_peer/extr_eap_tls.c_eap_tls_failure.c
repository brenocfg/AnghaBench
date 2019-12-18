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
struct eap_tls_data {int /*<<< orphan*/  eap_type; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_peer_tls_build_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_tls_failure(struct eap_sm *sm,
				       struct eap_tls_data *data,
				       struct eap_method_ret *ret, int res,
				       struct wpabuf *resp, u8 id)
{
	wpa_printf(MSG_DEBUG, "EAP-TLS: TLS processing failed");

	ret->methodState = METHOD_DONE;
	ret->decision = DECISION_FAIL;

	if (resp) {
		/*
		 * This is likely an alert message, so send it instead of just
		 * ACKing the error.
		 */
		return resp;
	}

	return eap_peer_tls_build_ack(id, data->eap_type, 0);
}