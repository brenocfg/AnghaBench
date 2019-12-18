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
struct gas_server_response {scalar_t__ offset; int /*<<< orphan*/  list; int /*<<< orphan*/ * resp; TYPE_1__* handler; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* status_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gas_server_free_response (struct gas_server_response*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpabuf_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gas_server_handle_tx_status(struct gas_server_response *response,
					int ack)
{
	if (ack && response->offset < wpabuf_len(response->resp)) {
		wpa_printf(MSG_DEBUG,
			   "GAS: More fragments remaining - keep pending entry");
		return;
	}

	if (!ack)
		wpa_printf(MSG_DEBUG,
			   "GAS: No ACK received - drop pending entry");
	else
		wpa_printf(MSG_DEBUG,
			   "GAS: Last fragment of the response sent out - drop pending entry");

	response->handler->status_cb(response->handler->ctx,
				     response->resp, ack);
	response->resp = NULL;
	dl_list_del(&response->list);
	gas_server_free_response(response);
}