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
struct wpa_supplicant {scalar_t__ dpp_gas_dialog_token; int /*<<< orphan*/  gas; scalar_t__ dpp_gas_client; int /*<<< orphan*/ * dpp_pkex; int /*<<< orphan*/ * dpp_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpp_auth_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpp_pkex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gas_query_stop (int /*<<< orphan*/ ,scalar_t__) ; 

void wpas_dpp_stop(struct wpa_supplicant *wpa_s)
{
	dpp_auth_deinit(wpa_s->dpp_auth);
	wpa_s->dpp_auth = NULL;
	dpp_pkex_free(wpa_s->dpp_pkex);
	wpa_s->dpp_pkex = NULL;
	if (wpa_s->dpp_gas_client && wpa_s->dpp_gas_dialog_token >= 0)
		gas_query_stop(wpa_s->gas, wpa_s->dpp_gas_dialog_token);
}