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
struct eap_ttls_data {int /*<<< orphan*/  ttls_version; int /*<<< orphan*/  ssl; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ eap_peer_tls_encrypt (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,struct wpabuf**) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 

__attribute__((used)) static int eap_ttls_encrypt_response(struct eap_sm *sm,
				     struct eap_ttls_data *data,
				     struct wpabuf *resp, u8 identifier,
				     struct wpabuf **out_data)
{
	if (resp == NULL)
		return 0;

	wpa_hexdump_buf_key(MSG_DEBUG, "EAP-TTLS: Encrypting Phase 2 data",
			    resp);
	if (eap_peer_tls_encrypt(sm, &data->ssl, EAP_TYPE_TTLS,
				 data->ttls_version, identifier,
				 resp, out_data)) {
		wpa_printf(MSG_INFO, "EAP-TTLS: Failed to encrypt a Phase 2 "
			   "frame");
		wpabuf_clear_free(resp);
		return -1;
	}
	wpabuf_clear_free(resp);

	return 0;
}