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
struct eap_ssl_data {scalar_t__ state; int /*<<< orphan*/  tmpbuf; int /*<<< orphan*/ * tls_in; } ;

/* Variables and functions */
 int EAP_TLS_FLAGS_LENGTH_INCLUDED ; 
 int EAP_TLS_FLAGS_MORE_FRAGMENTS ; 
 scalar_t__ FRAG_ACK ; 
 scalar_t__ MSG ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ WAIT_FRAG_ACK ; 
 unsigned int WPA_GET_BE32 (int const*) ; 
 scalar_t__ eap_server_tls_process_cont (struct eap_ssl_data*,int const*,int) ; 
 scalar_t__ eap_server_tls_process_fragment (struct eap_ssl_data*,int,unsigned int,int const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_set (int /*<<< orphan*/ *,int const*,int) ; 

__attribute__((used)) static int eap_server_tls_reassemble(struct eap_ssl_data *data, u8 flags,
				     const u8 **pos, size_t *left)
{
	unsigned int tls_msg_len = 0;
	const u8 *end = *pos + *left;

	wpa_hexdump(MSG_MSGDUMP, "SSL: Received data", *pos, *left);

	if (flags & EAP_TLS_FLAGS_LENGTH_INCLUDED) {
		if (*left < 4) {
			wpa_printf(MSG_INFO, "SSL: Short frame with TLS "
				   "length");
			return -1;
		}
		tls_msg_len = WPA_GET_BE32(*pos);
		wpa_printf(MSG_DEBUG, "SSL: TLS Message Length: %d",
			   tls_msg_len);
		*pos += 4;
		*left -= 4;

		if (*left > tls_msg_len) {
			wpa_printf(MSG_INFO, "SSL: TLS Message Length (%d "
				   "bytes) smaller than this fragment (%d "
				   "bytes)", (int) tls_msg_len, (int) *left);
			return -1;
		}
	}

	wpa_printf(MSG_DEBUG, "SSL: Received packet: Flags 0x%x "
		   "Message Length %u", flags, tls_msg_len);

	if (data->state == WAIT_FRAG_ACK) {
		if (*left != 0) {
			wpa_printf(MSG_DEBUG, "SSL: Unexpected payload in "
				   "WAIT_FRAG_ACK state");
			return -1;
		}
		wpa_printf(MSG_DEBUG, "SSL: Fragment acknowledged");
		return 1;
	}

	if (data->tls_in &&
	    eap_server_tls_process_cont(data, *pos, end - *pos) < 0)
		return -1;

	if (flags & EAP_TLS_FLAGS_MORE_FRAGMENTS) {
		if (eap_server_tls_process_fragment(data, flags, tls_msg_len,
						    *pos, end - *pos) < 0)
			return -1;

		data->state = FRAG_ACK;
		return 1;
	}

	if (data->state == FRAG_ACK) {
		wpa_printf(MSG_DEBUG, "SSL: All fragments received");
		data->state = MSG;
	}

	if (data->tls_in == NULL) {
		/* Wrap unfragmented messages as wpabuf without extra copy */
		wpabuf_set(&data->tmpbuf, *pos, end - *pos);
		data->tls_in = &data->tmpbuf;
	}

	return 0;
}