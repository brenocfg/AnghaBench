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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_sim_data {int* ver_list; int ver_list_len; int selected_version; int num_id_req; } ;
struct eap_sim_attrs {int version_list_len; int id_req; int /*<<< orphan*/ * version_list; } ;

/* Variables and functions */
#define  ANY_ID 131 
 int /*<<< orphan*/  EAP_SIM_UNABLE_TO_PROCESS_PACKET ; 
 int /*<<< orphan*/  EAP_SIM_UNSUPPORTED_VERSION ; 
#define  FULLAUTH_ID 130 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  NO_ID_REQ 129 
#define  PERMANENT_ID 128 
 struct wpabuf* eap_sim_client_error (struct eap_sim_data*,int,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_response_start (struct eap_sm*,struct eap_sim_data*,int,int) ; 
 scalar_t__ eap_sim_supported_ver (int) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int* os_memdup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_sim_process_start(struct eap_sm *sm,
					     struct eap_sim_data *data, u8 id,
					     struct eap_sim_attrs *attr)
{
	int selected_version = -1, id_error;
	size_t i;
	u8 *pos;

	wpa_printf(MSG_DEBUG, "EAP-SIM: subtype Start");
	if (attr->version_list == NULL) {
		wpa_printf(MSG_INFO, "EAP-SIM: No AT_VERSION_LIST in "
			   "SIM/Start");
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNSUPPORTED_VERSION);
	}

	os_free(data->ver_list);
	data->ver_list = os_memdup(attr->version_list, attr->version_list_len);
	if (data->ver_list == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-SIM: Failed to allocate "
			   "memory for version list");
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNABLE_TO_PROCESS_PACKET);
	}
	data->ver_list_len = attr->version_list_len;
	pos = data->ver_list;
	for (i = 0; i < data->ver_list_len / 2; i++) {
		int ver = pos[0] * 256 + pos[1];
		pos += 2;
		if (eap_sim_supported_ver(ver)) {
			selected_version = ver;
			break;
		}
	}
	if (selected_version < 0) {
		wpa_printf(MSG_INFO, "EAP-SIM: Could not find a supported "
			   "version");
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNSUPPORTED_VERSION);
	}
	wpa_printf(MSG_DEBUG, "EAP-SIM: Selected Version %d",
		   selected_version);
	data->selected_version = selected_version;

	id_error = 0;
	switch (attr->id_req) {
	case NO_ID_REQ:
		break;
	case ANY_ID:
		if (data->num_id_req > 0)
			id_error++;
		data->num_id_req++;
		break;
	case FULLAUTH_ID:
		if (data->num_id_req > 1)
			id_error++;
		data->num_id_req++;
		break;
	case PERMANENT_ID:
		if (data->num_id_req > 2)
			id_error++;
		data->num_id_req++;
		break;
	}
	if (id_error) {
		wpa_printf(MSG_INFO, "EAP-SIM: Too many ID requests "
			   "used within one authentication");
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNABLE_TO_PROCESS_PACKET);
	}

	return eap_sim_response_start(sm, data, id, attr->id_req);
}