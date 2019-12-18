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
struct eap_sm {int dummy; } ;
struct eap_peap_data {int /*<<< orphan*/  ssl; } ;
struct eap_hdr {int /*<<< orphan*/  length; int /*<<< orphan*/  identifier; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_FAILURE ; 
 int /*<<< orphan*/  EAP_CODE_SUCCESS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_server_tls_encrypt (struct eap_sm*,int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  host_to_be16 (size_t) ; 
 int /*<<< orphan*/  os_free (struct eap_hdr*) ; 
 struct eap_hdr* os_zalloc (size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,struct eap_hdr*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_peap_build_phase2_term(struct eap_sm *sm,
						  struct eap_peap_data *data,
						  u8 id, int success)
{
	struct wpabuf *encr_req, msgbuf;
	size_t req_len;
	struct eap_hdr *hdr;

	req_len = sizeof(*hdr);
	hdr = os_zalloc(req_len);
	if (hdr == NULL)
		return NULL;

	hdr->code = success ? EAP_CODE_SUCCESS : EAP_CODE_FAILURE;
	hdr->identifier = id;
	hdr->length = host_to_be16(req_len);

	wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: Encrypting Phase 2 data",
			(u8 *) hdr, req_len);

	wpabuf_set(&msgbuf, hdr, req_len);
	encr_req = eap_server_tls_encrypt(sm, &data->ssl, &msgbuf);
	os_free(hdr);

	return encr_req;
}