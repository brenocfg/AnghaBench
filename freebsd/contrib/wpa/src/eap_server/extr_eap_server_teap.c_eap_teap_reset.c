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
struct eap_teap_data {int /*<<< orphan*/  pac_opaque_encr; int /*<<< orphan*/  cmk_emsk; int /*<<< orphan*/  cmk_msk; int /*<<< orphan*/  simck_emsk; int /*<<< orphan*/  simck_msk; int /*<<< orphan*/  identity; int /*<<< orphan*/  peer_outer_tlvs; int /*<<< orphan*/  server_outer_tlvs; int /*<<< orphan*/  pending_phase2_resp; int /*<<< orphan*/  srv_id_info; int /*<<< orphan*/  srv_id; int /*<<< orphan*/  ssl; scalar_t__ phase2_priv; TYPE_1__* phase2_method; } ;
struct eap_sm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct eap_sm*,scalar_t__) ;} ;

/* Variables and functions */
 int EAP_TEAP_CMK_LEN ; 
 int EAP_TEAP_SIMCK_LEN ; 
 int /*<<< orphan*/  bin_clear_free (struct eap_teap_data*,int) ; 
 int /*<<< orphan*/  eap_server_tls_ssl_deinit (struct eap_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct eap_sm*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_teap_reset(struct eap_sm *sm, void *priv)
{
	struct eap_teap_data *data = priv;

	if (!data)
		return;
	if (data->phase2_priv && data->phase2_method)
		data->phase2_method->reset(sm, data->phase2_priv);
	eap_server_tls_ssl_deinit(sm, &data->ssl);
	os_free(data->srv_id);
	os_free(data->srv_id_info);
	wpabuf_free(data->pending_phase2_resp);
	wpabuf_free(data->server_outer_tlvs);
	wpabuf_free(data->peer_outer_tlvs);
	os_free(data->identity);
	forced_memzero(data->simck_msk, EAP_TEAP_SIMCK_LEN);
	forced_memzero(data->simck_emsk, EAP_TEAP_SIMCK_LEN);
	forced_memzero(data->cmk_msk, EAP_TEAP_CMK_LEN);
	forced_memzero(data->cmk_emsk, EAP_TEAP_CMK_LEN);
	forced_memzero(data->pac_opaque_encr, sizeof(data->pac_opaque_encr));
	bin_clear_free(data, sizeof(*data));
}