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
struct TYPE_2__ {int /*<<< orphan*/  erp_add_key; int /*<<< orphan*/  erp_get_key; int /*<<< orphan*/  eapol_event; int /*<<< orphan*/  tx_key; int /*<<< orphan*/  abort_auth; int /*<<< orphan*/  set_port_authorized; int /*<<< orphan*/  logger; int /*<<< orphan*/  sta_entry_alive; int /*<<< orphan*/  get_eap_user; int /*<<< orphan*/  finished; int /*<<< orphan*/  aaa_send; int /*<<< orphan*/  eapol_send; } ;
struct eapol_authenticator {int default_wep_key_idx; TYPE_1__ cb; int /*<<< orphan*/  conf; } ;
struct eapol_auth_config {scalar_t__ individual_wep_key_len; } ;
struct eapol_auth_cb {int /*<<< orphan*/  erp_add_key; int /*<<< orphan*/  erp_get_key; int /*<<< orphan*/  eapol_event; int /*<<< orphan*/  tx_key; int /*<<< orphan*/  abort_auth; int /*<<< orphan*/  set_port_authorized; int /*<<< orphan*/  logger; int /*<<< orphan*/  sta_entry_alive; int /*<<< orphan*/  get_eap_user; int /*<<< orphan*/  finished; int /*<<< orphan*/  aaa_send; int /*<<< orphan*/  eapol_send; } ;

/* Variables and functions */
 scalar_t__ eapol_auth_conf_clone (int /*<<< orphan*/ *,struct eapol_auth_config*) ; 
 int /*<<< orphan*/  os_free (struct eapol_authenticator*) ; 
 struct eapol_authenticator* os_zalloc (int) ; 

struct eapol_authenticator * eapol_auth_init(struct eapol_auth_config *conf,
					     struct eapol_auth_cb *cb)
{
	struct eapol_authenticator *eapol;

	eapol = os_zalloc(sizeof(*eapol));
	if (eapol == NULL)
		return NULL;

	if (eapol_auth_conf_clone(&eapol->conf, conf) < 0) {
		os_free(eapol);
		return NULL;
	}

	if (conf->individual_wep_key_len > 0) {
		/* use key0 in individual key and key1 in broadcast key */
		eapol->default_wep_key_idx = 1;
	}

	eapol->cb.eapol_send = cb->eapol_send;
	eapol->cb.aaa_send = cb->aaa_send;
	eapol->cb.finished = cb->finished;
	eapol->cb.get_eap_user = cb->get_eap_user;
	eapol->cb.sta_entry_alive = cb->sta_entry_alive;
	eapol->cb.logger = cb->logger;
	eapol->cb.set_port_authorized = cb->set_port_authorized;
	eapol->cb.abort_auth = cb->abort_auth;
	eapol->cb.tx_key = cb->tx_key;
	eapol->cb.eapol_event = cb->eapol_event;
	eapol->cb.erp_get_key = cb->erp_get_key;
	eapol->cb.erp_add_key = cb->erp_add_key;

	return eapol;
}