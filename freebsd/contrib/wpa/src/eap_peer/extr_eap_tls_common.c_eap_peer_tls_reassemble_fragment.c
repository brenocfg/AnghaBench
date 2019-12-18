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
struct wpabuf {int dummy; } ;
struct eap_ssl_data {size_t tls_in_left; struct wpabuf const* tls_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  eap_peer_tls_reset_input (struct eap_ssl_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 size_t wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf const*,struct wpabuf const*) ; 
 scalar_t__ wpabuf_resize (struct wpabuf const**,size_t) ; 

__attribute__((used)) static int eap_peer_tls_reassemble_fragment(struct eap_ssl_data *data,
					    const struct wpabuf *in_data)
{
	size_t tls_in_len, in_len;

	tls_in_len = data->tls_in ? wpabuf_len(data->tls_in) : 0;
	in_len = in_data ? wpabuf_len(in_data) : 0;

	if (tls_in_len + in_len == 0) {
		/* No message data received?! */
		wpa_printf(MSG_WARNING, "SSL: Invalid reassembly state: "
			   "tls_in_left=%lu tls_in_len=%lu in_len=%lu",
			   (unsigned long) data->tls_in_left,
			   (unsigned long) tls_in_len,
			   (unsigned long) in_len);
		eap_peer_tls_reset_input(data);
		return -1;
	}

	if (tls_in_len + in_len > 65536) {
		/*
		 * Limit length to avoid rogue servers from causing large
		 * memory allocations.
		 */
		wpa_printf(MSG_INFO, "SSL: Too long TLS fragment (size over "
			   "64 kB)");
		eap_peer_tls_reset_input(data);
		return -1;
	}

	if (in_len > data->tls_in_left) {
		/* Sender is doing something odd - reject message */
		wpa_printf(MSG_INFO, "SSL: more data than TLS message length "
			   "indicated");
		eap_peer_tls_reset_input(data);
		return -1;
	}

	if (wpabuf_resize(&data->tls_in, in_len) < 0) {
		wpa_printf(MSG_INFO, "SSL: Could not allocate memory for TLS "
			   "data");
		eap_peer_tls_reset_input(data);
		return -1;
	}
	if (in_data)
		wpabuf_put_buf(data->tls_in, in_data);
	data->tls_in_left -= in_len;

	if (data->tls_in_left > 0) {
		wpa_printf(MSG_DEBUG, "SSL: Need %lu bytes more input "
			   "data", (unsigned long) data->tls_in_left);
		return 1;
	}

	return 0;
}