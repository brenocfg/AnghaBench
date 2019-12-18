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
struct wpa_supplicant {int dummy; } ;
struct wpa_radio_work {scalar_t__ started; struct gas_query_pending* ctx; } ;
struct gas_query_pending {struct gas_query* gas; } ;
struct gas_query {struct wpa_radio_work* work; struct wpa_supplicant* wpa_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAS_QUERY_DELETED_AT_DEINIT ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  gas_query_done (struct gas_query*,struct gas_query_pending*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gas_query_free (struct gas_query_pending*,int) ; 
 int /*<<< orphan*/  gas_query_tx_initial_req (struct gas_query*,struct gas_query_pending*) ; 
 int /*<<< orphan*/  radio_work_done (struct wpa_radio_work*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpas_update_random_addr_disassoc (struct wpa_supplicant*) ; 

__attribute__((used)) static void gas_query_start_cb(struct wpa_radio_work *work, int deinit)
{
	struct gas_query_pending *query = work->ctx;
	struct gas_query *gas = query->gas;
	struct wpa_supplicant *wpa_s = gas->wpa_s;

	if (deinit) {
		if (work->started) {
			gas->work = NULL;
			gas_query_done(gas, query, GAS_QUERY_DELETED_AT_DEINIT);
			return;
		}

		gas_query_free(query, 1);
		return;
	}

	if (wpas_update_random_addr_disassoc(wpa_s) < 0) {
		wpa_msg(wpa_s, MSG_INFO,
			"Failed to assign random MAC address for GAS");
		gas_query_free(query, 1);
		radio_work_done(work);
		return;
	}

	gas->work = work;
	gas_query_tx_initial_req(gas, query);
}