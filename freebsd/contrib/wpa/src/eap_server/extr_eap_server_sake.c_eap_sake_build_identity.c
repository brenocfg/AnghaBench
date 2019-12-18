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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int server_id_len; int /*<<< orphan*/ * server_id; } ;
struct eap_sake_data {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SAKE_AT_PERM_ID_REQ ; 
 int /*<<< orphan*/  EAP_SAKE_AT_SERVERID ; 
 int /*<<< orphan*/  EAP_SAKE_SUBTYPE_IDENTITY ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sake_add_attr (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct wpabuf* eap_sake_build_msg (struct eap_sake_data*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_sake_build_identity(struct eap_sm *sm,
					       struct eap_sake_data *data,
					       u8 id)
{
	struct wpabuf *msg;
	size_t plen;

	wpa_printf(MSG_DEBUG, "EAP-SAKE: Request/Identity");

	plen = 4;
	plen += 2 + sm->server_id_len;
	msg = eap_sake_build_msg(data, id, plen, EAP_SAKE_SUBTYPE_IDENTITY);
	if (msg == NULL) {
		data->state = FAILURE;
		return NULL;
	}

	wpa_printf(MSG_DEBUG, "EAP-SAKE: * AT_PERM_ID_REQ");
	eap_sake_add_attr(msg, EAP_SAKE_AT_PERM_ID_REQ, NULL, 2);

	wpa_printf(MSG_DEBUG, "EAP-SAKE: * AT_SERVERID");
	eap_sake_add_attr(msg, EAP_SAKE_AT_SERVERID,
			  sm->server_id, sm->server_id_len);

	return msg;
}