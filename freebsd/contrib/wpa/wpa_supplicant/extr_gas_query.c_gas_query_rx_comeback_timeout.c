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
struct gas_query_pending {int retry; int dialog_token; int /*<<< orphan*/ * adv_proto; scalar_t__ next_frag_id; scalar_t__ wait_comeback; int /*<<< orphan*/  req; int /*<<< orphan*/  addr; } ;
struct gas_query {struct gas_query_pending* current; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct gas_query*,struct gas_query_pending*) ; 
 int gas_query_new_dialog_token (struct gas_query*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gas_query_timeout ; 
 int /*<<< orphan*/  gas_query_tx_comeback_timeout ; 
 int /*<<< orphan*/  gas_query_tx_initial_req (struct gas_query*,struct gas_query_pending*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 int* wpabuf_mhead_u8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gas_query_rx_comeback_timeout(void *eloop_data, void *user_ctx)
{
	struct gas_query *gas = eloop_data;
	struct gas_query_pending *query = user_ctx;
	int dialog_token;

	wpa_printf(MSG_DEBUG,
		   "GAS: No response to comeback request received (retry=%u)",
		   query->retry);
	if (gas->current != query || query->retry)
		return;
	dialog_token = gas_query_new_dialog_token(gas, query->addr);
	if (dialog_token < 0)
		return;
	wpa_printf(MSG_DEBUG,
		   "GAS: Retry GAS query due to comeback response timeout");
	query->retry = 1;
	query->dialog_token = dialog_token;
	*(wpabuf_mhead_u8(query->req) + 2) = dialog_token;
	query->wait_comeback = 0;
	query->next_frag_id = 0;
	wpabuf_free(query->adv_proto);
	query->adv_proto = NULL;
	eloop_cancel_timeout(gas_query_tx_comeback_timeout, gas, query);
	eloop_cancel_timeout(gas_query_timeout, gas, query);
	gas_query_tx_initial_req(gas, query);
}