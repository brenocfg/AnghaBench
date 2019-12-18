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
struct eap_sm {int server_id_len; int /*<<< orphan*/  server_id; } ;
struct eap_eke_data {int serverid_type; struct wpabuf* msgs; } ;

/* Variables and functions */
 int EAP_EKE_DHGROUP_EKE_14 ; 
 int EAP_EKE_DHGROUP_EKE_15 ; 
 int EAP_EKE_DHGROUP_EKE_16 ; 
 int EAP_EKE_ENCR_AES128_CBC ; 
 int /*<<< orphan*/  EAP_EKE_ID ; 
 int EAP_EKE_MAC_HMAC_SHA1 ; 
 int EAP_EKE_MAC_HMAC_SHA2_256 ; 
 int EAP_EKE_PRF_HMAC_SHA1 ; 
 int EAP_EKE_PRF_HMAC_SHA2_256 ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_eke_build_msg (struct eap_eke_data*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_dup (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_eke_build_identity(struct eap_sm *sm,
					      struct eap_eke_data *data,
					      u8 id)
{
	struct wpabuf *msg;
	size_t plen;

	wpa_printf(MSG_DEBUG, "EAP-EKE: Request/Identity");

	plen = 2 + 4 * 4 + 1 + sm->server_id_len;
	msg = eap_eke_build_msg(data, id, plen, EAP_EKE_ID);
	if (msg == NULL)
		return NULL;

	wpabuf_put_u8(msg, 4); /* NumProposals */
	wpabuf_put_u8(msg, 0); /* Reserved */

	/* Proposal - DH Group 16 with AES128-CBC and SHA256 */
	wpabuf_put_u8(msg, EAP_EKE_DHGROUP_EKE_16); /* Group Description */
	wpabuf_put_u8(msg, EAP_EKE_ENCR_AES128_CBC); /* Encryption */
	wpabuf_put_u8(msg, EAP_EKE_PRF_HMAC_SHA2_256); /* PRF */
	wpabuf_put_u8(msg, EAP_EKE_MAC_HMAC_SHA2_256); /* MAC */

	/* Proposal - DH Group 15 with AES128-CBC and SHA256 */
	wpabuf_put_u8(msg, EAP_EKE_DHGROUP_EKE_15); /* Group Description */
	wpabuf_put_u8(msg, EAP_EKE_ENCR_AES128_CBC); /* Encryption */
	wpabuf_put_u8(msg, EAP_EKE_PRF_HMAC_SHA2_256); /* PRF */
	wpabuf_put_u8(msg, EAP_EKE_MAC_HMAC_SHA2_256); /* MAC */

	/* Proposal - DH Group 14 with AES128-CBC and SHA256 */
	wpabuf_put_u8(msg, EAP_EKE_DHGROUP_EKE_14); /* Group Description */
	wpabuf_put_u8(msg, EAP_EKE_ENCR_AES128_CBC); /* Encryption */
	wpabuf_put_u8(msg, EAP_EKE_PRF_HMAC_SHA2_256); /* PRF */
	wpabuf_put_u8(msg, EAP_EKE_MAC_HMAC_SHA2_256); /* MAC */

	/*
	 * Proposal - DH Group 14 with AES128-CBC and SHA1
	 * (mandatory to implement algorithms)
	 */
	wpabuf_put_u8(msg, EAP_EKE_DHGROUP_EKE_14); /* Group Description */
	wpabuf_put_u8(msg, EAP_EKE_ENCR_AES128_CBC); /* Encryption */
	wpabuf_put_u8(msg, EAP_EKE_PRF_HMAC_SHA1); /* PRF */
	wpabuf_put_u8(msg, EAP_EKE_MAC_HMAC_SHA1); /* MAC */

	/* Server IDType + Identity */
	wpabuf_put_u8(msg, data->serverid_type);
	wpabuf_put_data(msg, sm->server_id, sm->server_id_len);

	wpabuf_free(data->msgs);
	data->msgs = wpabuf_dup(msg);
	if (data->msgs == NULL) {
		wpabuf_free(msg);
		return NULL;
	}

	return msg;
}