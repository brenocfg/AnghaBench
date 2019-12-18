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
struct hostapd_data {int /*<<< orphan*/ * eap_sim_db_priv; int /*<<< orphan*/ * ssl_ctx; int /*<<< orphan*/ * radius_srv; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_sim_db_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_server_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_deinit (int /*<<< orphan*/ *) ; 

void authsrv_deinit(struct hostapd_data *hapd)
{
#ifdef RADIUS_SERVER
	radius_server_deinit(hapd->radius_srv);
	hapd->radius_srv = NULL;
#endif /* RADIUS_SERVER */

#ifdef EAP_TLS_FUNCS
	if (hapd->ssl_ctx) {
		tls_deinit(hapd->ssl_ctx);
		hapd->ssl_ctx = NULL;
	}
#endif /* EAP_TLS_FUNCS */

#ifdef EAP_SIM_DB
	if (hapd->eap_sim_db_priv) {
		eap_sim_db_deinit(hapd->eap_sim_db_priv);
		hapd->eap_sim_db_priv = NULL;
	}
#endif /* EAP_SIM_DB */
}