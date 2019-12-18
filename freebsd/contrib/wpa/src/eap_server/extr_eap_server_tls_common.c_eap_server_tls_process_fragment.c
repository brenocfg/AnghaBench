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
typedef  int u8 ;
typedef  int u32 ;
struct eap_ssl_data {int /*<<< orphan*/ * tls_in; } ;

/* Variables and functions */
 int EAP_TLS_FLAGS_LENGTH_INCLUDED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int const*,size_t) ; 
 scalar_t__ wpabuf_tailroom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eap_server_tls_process_fragment(struct eap_ssl_data *data,
					   u8 flags, u32 message_length,
					   const u8 *buf, size_t len)
{
	/* Process a fragment that is not the last one of the message */
	if (data->tls_in == NULL && !(flags & EAP_TLS_FLAGS_LENGTH_INCLUDED)) {
		wpa_printf(MSG_DEBUG, "SSL: No Message Length field in a "
			   "fragmented packet");
		return -1;
	}

	if (data->tls_in == NULL) {
		/* First fragment of the message */

		/* Limit length to avoid rogue peers from causing large
		 * memory allocations. */
		if (message_length > 65536) {
			wpa_printf(MSG_INFO, "SSL: Too long TLS fragment (size"
				   " over 64 kB)");
			return -1;
		}

		if (len > message_length) {
			wpa_printf(MSG_INFO, "SSL: Too much data (%d bytes) in "
				   "first fragment of frame (TLS Message "
				   "Length %d bytes)",
				   (int) len, (int) message_length);
			return -1;
		}

		data->tls_in = wpabuf_alloc(message_length);
		if (data->tls_in == NULL) {
			wpa_printf(MSG_DEBUG, "SSL: No memory for message");
			return -1;
		}
		wpabuf_put_data(data->tls_in, buf, len);
		wpa_printf(MSG_DEBUG, "SSL: Received %lu bytes in first "
			   "fragment, waiting for %lu bytes more",
			   (unsigned long) len,
			   (unsigned long) wpabuf_tailroom(data->tls_in));
	}

	return 0;
}