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
struct eap_sake_hdr {int /*<<< orphan*/  subtype; int /*<<< orphan*/  session_id; int /*<<< orphan*/  version; } ;
struct eap_sake_data {int /*<<< orphan*/  session_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SAKE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_SAKE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct eap_sake_hdr* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_sake_build_msg(struct eap_sake_data *data,
					  int id, size_t length, u8 subtype)
{
	struct eap_sake_hdr *sake;
	struct wpabuf *msg;
	size_t plen;

	plen = length + sizeof(struct eap_sake_hdr);

	msg = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_SAKE, plen,
			    EAP_CODE_RESPONSE, id);
	if (msg == NULL) {
		wpa_printf(MSG_ERROR, "EAP-SAKE: Failed to allocate memory "
			   "request");
		return NULL;
	}

	sake = wpabuf_put(msg, sizeof(*sake));
	sake->version = EAP_SAKE_VERSION;
	sake->session_id = data->session_id;
	sake->subtype = subtype;

	return msg;
}