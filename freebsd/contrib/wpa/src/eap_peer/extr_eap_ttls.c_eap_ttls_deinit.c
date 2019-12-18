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
struct eap_ttls_data {int /*<<< orphan*/  pending_resp; int /*<<< orphan*/  pending_phase2_req; struct eap_ttls_data* session_id; int /*<<< orphan*/  ssl; struct eap_ttls_data* phase2_eap_types; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_peer_tls_ssl_deinit (struct eap_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_ttls_free_key (struct eap_ttls_data*) ; 
 int /*<<< orphan*/  eap_ttls_phase2_eap_deinit (struct eap_sm*,struct eap_ttls_data*) ; 
 int /*<<< orphan*/  os_free (struct eap_ttls_data*) ; 
 int /*<<< orphan*/  wpabuf_clear_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_ttls_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_ttls_data *data = priv;
	if (data == NULL)
		return;
	eap_ttls_phase2_eap_deinit(sm, data);
	os_free(data->phase2_eap_types);
	eap_peer_tls_ssl_deinit(sm, &data->ssl);
	eap_ttls_free_key(data);
	os_free(data->session_id);
	wpabuf_clear_free(data->pending_phase2_req);
	wpabuf_clear_free(data->pending_resp);
	os_free(data);
}