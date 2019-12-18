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
typedef  scalar_t__ u8 ;
typedef  struct wpabuf const wpabuf ;
struct eap_sm {int dummy; } ;
struct eap_sim_attrs {int id_req; } ;
struct eap_aka_data {int num_id_req; scalar_t__ prev_id; } ;

/* Variables and functions */
#define  ANY_ID 131 
 int /*<<< orphan*/  EAP_AKA_UNABLE_TO_PROCESS_PACKET ; 
#define  FULLAUTH_ID 130 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  NO_ID_REQ 129 
#define  PERMANENT_ID 128 
 int /*<<< orphan*/  eap_aka_add_id_msg (struct eap_aka_data*,struct wpabuf const*) ; 
 struct wpabuf const* eap_aka_client_error (struct eap_aka_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct wpabuf const* eap_aka_response_identity (struct eap_sm*,struct eap_aka_data*,scalar_t__,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_aka_process_identity(struct eap_sm *sm,
						struct eap_aka_data *data,
						u8 id,
						const struct wpabuf *reqData,
						struct eap_sim_attrs *attr)
{
	int id_error;
	struct wpabuf *buf;

	wpa_printf(MSG_DEBUG, "EAP-AKA: subtype Identity");

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
		wpa_printf(MSG_INFO, "EAP-AKA: Too many ID requests "
			   "used within one authentication");
		return eap_aka_client_error(data, id,
					    EAP_AKA_UNABLE_TO_PROCESS_PACKET);
	}

	buf = eap_aka_response_identity(sm, data, id, attr->id_req);

	if (data->prev_id != id) {
		eap_aka_add_id_msg(data, reqData);
		eap_aka_add_id_msg(data, buf);
		data->prev_id = id;
	}

	return buf;
}