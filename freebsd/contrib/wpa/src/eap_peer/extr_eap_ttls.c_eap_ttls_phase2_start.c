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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_ttls_data {int phase2_success; int /*<<< orphan*/  ttls_version; TYPE_1__ ssl; scalar_t__ reauth; scalar_t__ phase2_start; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;
struct eap_method_ret {int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_UNCOND_SUCC ; 
 int /*<<< orphan*/  EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_peer_tls_build_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int eap_ttls_implicit_identity_request (struct eap_sm*,struct eap_ttls_data*,struct eap_method_ret*,int /*<<< orphan*/ ,struct wpabuf**) ; 
 scalar_t__ tls_connection_resumed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_ttls_phase2_start(struct eap_sm *sm, struct eap_ttls_data *data,
				 struct eap_method_ret *ret, u8 identifier,
				 struct wpabuf **out_data)
{
	data->phase2_start = 0;

	/*
	 * EAP-TTLS does not use Phase2 on fast re-auth; this must be done only
	 * if TLS part was indeed resuming a previous session. Most
	 * Authentication Servers terminate EAP-TTLS before reaching this
	 * point, but some do not. Make wpa_supplicant stop phase 2 here, if
	 * needed.
	 */
	if (data->reauth &&
	    tls_connection_resumed(sm->ssl_ctx, data->ssl.conn)) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS: Session resumption - "
			   "skip phase 2");
		*out_data = eap_peer_tls_build_ack(identifier, EAP_TYPE_TTLS,
						   data->ttls_version);
		ret->methodState = METHOD_DONE;
		ret->decision = DECISION_UNCOND_SUCC;
		data->phase2_success = 1;
		return 0;
	}

	return eap_ttls_implicit_identity_request(sm, data, ret, identifier,
						  out_data);
}