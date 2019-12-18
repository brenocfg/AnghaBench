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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_peap_data {scalar_t__ peap_version; int /*<<< orphan*/  ssl; TYPE_1__* phase2_method; int /*<<< orphan*/ * phase2_priv; } ;
struct eap_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ method; struct wpabuf* (* buildReq ) (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_TLV ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_server_tls_encrypt (struct eap_sm*,int /*<<< orphan*/ *,struct wpabuf*) ; 
 struct wpabuf* stub1 (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_peap_build_phase2_req(struct eap_sm *sm,
						 struct eap_peap_data *data,
						 u8 id)
{
	struct wpabuf *buf, *encr_req, msgbuf;
	const u8 *req;
	size_t req_len;

	if (data->phase2_method == NULL || data->phase2_priv == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-PEAP: Phase 2 method not ready");
		return NULL;
	}
	buf = data->phase2_method->buildReq(sm, data->phase2_priv, id);
	if (buf == NULL)
		return NULL;

	req = wpabuf_head(buf);
	req_len = wpabuf_len(buf);
	wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: Encrypting Phase 2 data",
			req, req_len);

	if (data->peap_version == 0 &&
	    data->phase2_method->method != EAP_TYPE_TLV) {
		req += sizeof(struct eap_hdr);
		req_len -= sizeof(struct eap_hdr);
	}

	wpabuf_set(&msgbuf, req, req_len);
	encr_req = eap_server_tls_encrypt(sm, &data->ssl, &msgbuf);
	wpabuf_free(buf);

	return encr_req;
}