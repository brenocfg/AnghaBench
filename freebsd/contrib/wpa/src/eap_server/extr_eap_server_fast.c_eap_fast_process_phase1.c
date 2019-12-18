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
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  tls_out; int /*<<< orphan*/  conn; } ;
struct eap_fast_data {TYPE_1__ ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int eap_fast_phase1_done (struct eap_sm*,struct eap_fast_data*) ; 
 int /*<<< orphan*/  eap_fast_state (struct eap_fast_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_server_tls_phase1 (struct eap_sm*,TYPE_1__*) ; 
 int /*<<< orphan*/  tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpabuf_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_fast_process_phase1(struct eap_sm *sm,
				   struct eap_fast_data *data)
{
	if (eap_server_tls_phase1(sm, &data->ssl) < 0) {
		wpa_printf(MSG_INFO, "EAP-FAST: TLS processing failed");
		eap_fast_state(data, FAILURE);
		return -1;
	}

	if (!tls_connection_established(sm->ssl_ctx, data->ssl.conn) ||
	    wpabuf_len(data->ssl.tls_out) > 0)
		return 1;

	/*
	 * Phase 1 was completed with the received message (e.g., when using
	 * abbreviated handshake), so Phase 2 can be started immediately
	 * without having to send through an empty message to the peer.
	 */

	return eap_fast_phase1_done(sm, data);
}