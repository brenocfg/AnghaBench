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
struct eap_sim_db_pending {int dummy; } ;
struct eap_sim_db_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sim_db_del_pending (struct eap_sim_db_data*,struct eap_sim_db_pending*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct eap_sim_db_pending*) ; 

__attribute__((used)) static void eap_sim_db_del_timeout(void *eloop_ctx, void *user_ctx)
{
	struct eap_sim_db_data *data = eloop_ctx;
	struct eap_sim_db_pending *entry = user_ctx;

	wpa_printf(MSG_DEBUG, "EAP-SIM DB: Delete query timeout for %p", entry);
	eap_sim_db_del_pending(data, entry);
}