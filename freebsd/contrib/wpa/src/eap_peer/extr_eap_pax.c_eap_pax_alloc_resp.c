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
struct eap_pax_hdr {int /*<<< orphan*/  public_key_id; int /*<<< orphan*/  dh_group_id; int /*<<< orphan*/  mac_id; scalar_t__ flags; int /*<<< orphan*/  op_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_TYPE_PAX ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eap_pax_hdr* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_pax_alloc_resp(const struct eap_pax_hdr *req,
					  u8 id, u8 op_code, size_t plen)
{
	struct wpabuf *resp;
	struct eap_pax_hdr *pax;

	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_PAX,
			     sizeof(*pax) + plen, EAP_CODE_RESPONSE, id);
	if (resp == NULL)
		return NULL;

	pax = wpabuf_put(resp, sizeof(*pax));
	pax->op_code = op_code;
	pax->flags = 0;
	pax->mac_id = req->mac_id;
	pax->dh_group_id = req->dh_group_id;
	pax->public_key_id = req->public_key_id;

	return resp;
}