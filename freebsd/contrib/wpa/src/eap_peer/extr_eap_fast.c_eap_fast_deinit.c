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
struct eap_sm {int dummy; } ;
struct eap_fast_pac {struct eap_fast_pac* next; } ;
struct eap_fast_data {int /*<<< orphan*/  pending_resp; int /*<<< orphan*/  pending_phase2_req; struct eap_fast_data* session_id; int /*<<< orphan*/  emsk; int /*<<< orphan*/  key_data; struct eap_fast_pac* pac; int /*<<< orphan*/  ssl; struct eap_fast_data* key_block_p; struct eap_fast_data* phase2_types; scalar_t__ phase2_priv; TYPE_1__* phase2_method; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deinit ) (struct eap_sm*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_EMSK_LEN ; 
 int /*<<< orphan*/  EAP_FAST_KEY_LEN ; 
 int /*<<< orphan*/  eap_fast_free_pac (struct eap_fast_pac*) ; 
 int /*<<< orphan*/  eap_peer_tls_ssl_deinit (struct eap_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct eap_fast_data*) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct eap_sm*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_clear_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_fast_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_fast_data *data = priv;
	struct eap_fast_pac *pac, *prev;

	if (data == NULL)
		return;
	if (data->phase2_priv && data->phase2_method)
		data->phase2_method->deinit(sm, data->phase2_priv);
	os_free(data->phase2_types);
	os_free(data->key_block_p);
	eap_peer_tls_ssl_deinit(sm, &data->ssl);

	pac = data->pac;
	prev = NULL;
	while (pac) {
		prev = pac;
		pac = pac->next;
		eap_fast_free_pac(prev);
	}
	os_memset(data->key_data, 0, EAP_FAST_KEY_LEN);
	os_memset(data->emsk, 0, EAP_EMSK_LEN);
	os_free(data->session_id);
	wpabuf_clear_free(data->pending_phase2_req);
	wpabuf_clear_free(data->pending_resp);
	os_free(data);
}