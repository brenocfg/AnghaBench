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
struct eap_teap_data {int /*<<< orphan*/  simck_emsk; int /*<<< orphan*/  simck_msk; int /*<<< orphan*/ * peer_outer_tlvs; int /*<<< orphan*/ * server_outer_tlvs; int /*<<< orphan*/ * pending_resp; int /*<<< orphan*/ * pending_phase2_req; int /*<<< orphan*/ * session_id; int /*<<< orphan*/  emsk; int /*<<< orphan*/  key_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_EMSK_LEN ; 
 int /*<<< orphan*/  EAP_TEAP_KEY_LEN ; 
 int /*<<< orphan*/  EAP_TEAP_SIMCK_LEN ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eap_teap_clear(struct eap_teap_data *data)
{
	forced_memzero(data->key_data, EAP_TEAP_KEY_LEN);
	forced_memzero(data->emsk, EAP_EMSK_LEN);
	os_free(data->session_id);
	data->session_id = NULL;
	wpabuf_free(data->pending_phase2_req);
	data->pending_phase2_req = NULL;
	wpabuf_free(data->pending_resp);
	data->pending_resp = NULL;
	wpabuf_free(data->server_outer_tlvs);
	data->server_outer_tlvs = NULL;
	wpabuf_free(data->peer_outer_tlvs);
	data->peer_outer_tlvs = NULL;
	forced_memzero(data->simck_msk, EAP_TEAP_SIMCK_LEN);
	forced_memzero(data->simck_emsk, EAP_TEAP_SIMCK_LEN);
}