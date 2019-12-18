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
struct eap_sim_db_pending {int /*<<< orphan*/  cb_session_ctx; int /*<<< orphan*/  state; } ;
struct eap_sim_db_data {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* get_complete_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sim_db_del_timeout ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eap_sim_db_data*,struct eap_sim_db_pending*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct eap_sim_db_pending*) ; 

__attribute__((used)) static void eap_sim_db_query_timeout(void *eloop_ctx, void *user_ctx)
{
	struct eap_sim_db_data *data = eloop_ctx;
	struct eap_sim_db_pending *entry = user_ctx;

	/*
	 * Report failure and allow some time for EAP server to process it
	 * before deleting the query.
	 */
	wpa_printf(MSG_DEBUG, "EAP-SIM DB: Query timeout for %p", entry);
	entry->state = FAILURE;
	data->get_complete_cb(data->ctx, entry->cb_session_ctx);
	eloop_register_timeout(1, 0, eap_sim_db_del_timeout, data, entry);
}