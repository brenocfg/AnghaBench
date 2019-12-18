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
struct wpa_supplicant {int /*<<< orphan*/  conf; int /*<<< orphan*/ * ext_pw; int /*<<< orphan*/ * ctrl_iface; int /*<<< orphan*/  scard; int /*<<< orphan*/ * eapol; int /*<<< orphan*/ * wpa; } ;
struct extra_radius_attr {struct extra_radius_attr* next; struct extra_radius_attr* auth_server; struct extra_radius_attr* shared_secret; } ;
struct eapol_test_data {struct extra_radius_attr* extra_attrs; struct extra_radius_attr* radius_conf; struct extra_radius_attr* eap_identity; int /*<<< orphan*/ * last_recv_radius; int /*<<< orphan*/  last_eap_radius; int /*<<< orphan*/  radius; } ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_sm_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext_password_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct extra_radius_attr*) ; 
 int /*<<< orphan*/  radius_client_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scard_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_config_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_eapol_clean(struct eapol_test_data *e,
			     struct wpa_supplicant *wpa_s)
{
	struct extra_radius_attr *p, *prev;

	wpa_sm_deinit(wpa_s->wpa);
	wpa_s->wpa = NULL;
	radius_client_deinit(e->radius);
	wpabuf_free(e->last_eap_radius);
	radius_msg_free(e->last_recv_radius);
	e->last_recv_radius = NULL;
	os_free(e->eap_identity);
	e->eap_identity = NULL;
	eapol_sm_deinit(wpa_s->eapol);
	wpa_s->eapol = NULL;
	if (e->radius_conf && e->radius_conf->auth_server) {
		os_free(e->radius_conf->auth_server->shared_secret);
		os_free(e->radius_conf->auth_server);
	}
	os_free(e->radius_conf);
	e->radius_conf = NULL;
	scard_deinit(wpa_s->scard);
	if (wpa_s->ctrl_iface) {
		wpa_supplicant_ctrl_iface_deinit(wpa_s->ctrl_iface);
		wpa_s->ctrl_iface = NULL;
	}

	ext_password_deinit(wpa_s->ext_pw);
	wpa_s->ext_pw = NULL;

	wpa_config_free(wpa_s->conf);

	p = e->extra_attrs;
	while (p) {
		prev = p;
		p = p->next;
		os_free(prev);
	}
}