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
struct eap_fast_data {int /*<<< orphan*/  identity; int /*<<< orphan*/  pending_phase2_resp; int /*<<< orphan*/  key_block_p; int /*<<< orphan*/  srv_id_info; int /*<<< orphan*/  srv_id; int /*<<< orphan*/  ssl; scalar_t__ phase2_priv; TYPE_1__* phase2_method; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct eap_sm*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (struct eap_fast_data*,int) ; 
 int /*<<< orphan*/  eap_server_tls_ssl_deinit (struct eap_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct eap_sm*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_fast_reset(struct eap_sm *sm, void *priv)
{
	struct eap_fast_data *data = priv;
	if (data == NULL)
		return;
	if (data->phase2_priv && data->phase2_method)
		data->phase2_method->reset(sm, data->phase2_priv);
	eap_server_tls_ssl_deinit(sm, &data->ssl);
	os_free(data->srv_id);
	os_free(data->srv_id_info);
	os_free(data->key_block_p);
	wpabuf_free(data->pending_phase2_resp);
	os_free(data->identity);
	bin_clear_free(data, sizeof(*data));
}