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
struct wpabuf {int dummy; } ;
struct TYPE_2__ {struct wpabuf* tls_out; scalar_t__ tls_out_pos; } ;
struct eap_teap_data {TYPE_1__ ssl; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 struct wpabuf* eap_server_tls_encrypt (struct eap_sm*,TYPE_1__*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,scalar_t__) ; 

__attribute__((used)) static int eap_teap_encrypt_phase2(struct eap_sm *sm,
				   struct eap_teap_data *data,
				   struct wpabuf *plain, int piggyback)
{
	struct wpabuf *encr;

	wpa_hexdump_buf_key(MSG_DEBUG, "EAP-TEAP: Encrypting Phase 2 TLVs",
			    plain);
	encr = eap_server_tls_encrypt(sm, &data->ssl, plain);
	wpabuf_free(plain);

	if (!encr)
		return -1;

	if (data->ssl.tls_out && piggyback) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Piggyback Phase 2 data (len=%d) with last Phase 1 Message (len=%d used=%d)",
			   (int) wpabuf_len(encr),
			   (int) wpabuf_len(data->ssl.tls_out),
			   (int) data->ssl.tls_out_pos);
		if (wpabuf_resize(&data->ssl.tls_out, wpabuf_len(encr)) < 0) {
			wpa_printf(MSG_WARNING,
				   "EAP-TEAP: Failed to resize output buffer");
			wpabuf_free(encr);
			return -1;
		}
		wpabuf_put_buf(data->ssl.tls_out, encr);
		wpabuf_free(encr);
	} else {
		wpabuf_free(data->ssl.tls_out);
		data->ssl.tls_out_pos = 0;
		data->ssl.tls_out = encr;
	}

	return 0;
}