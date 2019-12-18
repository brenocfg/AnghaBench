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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_2__ {int tls_version; } ;
struct tlsv1_server {int client_version; scalar_t__ const* client_random; size_t num_cipher_suites; int* cipher_suites; int cipher_suite; scalar_t__ const* session_ticket; int session_ticket_len; int status_request; int /*<<< orphan*/  state; TYPE_1__ rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  SERVER_HELLO ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_ALERT_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  TLS_ALERT_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  TLS_COMPRESSION_NULL ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 int TLS_EXT_SESSION_TICKET ; 
 int TLS_EXT_STATUS_REQUEST ; 
 int TLS_EXT_STATUS_REQUEST_V2 ; 
 scalar_t__ const TLS_HANDSHAKE_TYPE_CLIENT_HELLO ; 
 int TLS_RANDOM_LEN ; 
 scalar_t__ const TLS_SESSION_ID_MAX_LEN ; 
 int TLS_VERSION ; 
 int TLS_VERSION_1 ; 
 int TLS_VERSION_1_1 ; 
 int TLS_VERSION_1_2 ; 
 void* WPA_GET_BE16 (scalar_t__ const*) ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
 int /*<<< orphan*/  os_free (scalar_t__ const*) ; 
 scalar_t__ const* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__ const*,scalar_t__ const*,int) ; 
 scalar_t__ testing_cipher_suite_filter (struct tlsv1_server*,int) ; 
 int /*<<< orphan*/  tls_process_status_request_v2 (struct tlsv1_server*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  tls_version_str (int) ; 
 scalar_t__ tlsv1_record_set_cipher_suite (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*,...) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,scalar_t__ const) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_process_client_hello(struct tlsv1_server *conn, u8 ct,
				    const u8 *in_data, size_t *in_len)
{
	const u8 *pos, *end, *c;
	size_t left, len, i, j;
	u16 cipher_suite;
	u16 num_suites;
	int compr_null_found;
	u16 ext_type, ext_len;

	if (ct != TLS_CONTENT_TYPE_HANDSHAKE) {
		tlsv1_server_log(conn, "Expected Handshake; received content type 0x%x",
				 ct);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	pos = in_data;
	left = *in_len;

	if (left < 4) {
		tlsv1_server_log(conn,
				 "Truncated handshake message (expected ClientHello)");
		goto decode_error;
	}

	/* HandshakeType msg_type */
	if (*pos != TLS_HANDSHAKE_TYPE_CLIENT_HELLO) {
		tlsv1_server_log(conn, "Received unexpected handshake message %d (expected ClientHello)",
				 *pos);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}
	tlsv1_server_log(conn, "Received ClientHello");
	pos++;
	/* uint24 length */
	len = WPA_GET_BE24(pos);
	pos += 3;
	left -= 4;

	if (len > left) {
		tlsv1_server_log(conn,
				 "Truncated ClientHello (len=%d left=%d)",
				 (int) len, (int) left);
		goto decode_error;
	}

	/* body - ClientHello */

	wpa_hexdump(MSG_MSGDUMP, "TLSv1: ClientHello", pos, len);
	end = pos + len;

	/* ProtocolVersion client_version */
	if (end - pos < 2) {
		tlsv1_server_log(conn, "Truncated ClientHello/client_version");
		goto decode_error;
	}
	conn->client_version = WPA_GET_BE16(pos);
	tlsv1_server_log(conn, "Client version %d.%d",
			 conn->client_version >> 8,
			 conn->client_version & 0xff);
	if (conn->client_version < TLS_VERSION_1) {
		tlsv1_server_log(conn, "Unexpected protocol version in ClientHello %u.%u",
				 conn->client_version >> 8,
				 conn->client_version & 0xff);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_PROTOCOL_VERSION);
		return -1;
	}
	pos += 2;

	if (TLS_VERSION == TLS_VERSION_1)
		conn->rl.tls_version = TLS_VERSION_1;
#ifdef CONFIG_TLSV12
	else if (conn->client_version >= TLS_VERSION_1_2)
		conn->rl.tls_version = TLS_VERSION_1_2;
#endif /* CONFIG_TLSV12 */
	else if (conn->client_version > TLS_VERSION_1_1)
		conn->rl.tls_version = TLS_VERSION_1_1;
	else
		conn->rl.tls_version = conn->client_version;
	tlsv1_server_log(conn, "Using TLS v%s",
			 tls_version_str(conn->rl.tls_version));

	/* Random random */
	if (end - pos < TLS_RANDOM_LEN) {
		tlsv1_server_log(conn, "Truncated ClientHello/client_random");
		goto decode_error;
	}

	os_memcpy(conn->client_random, pos, TLS_RANDOM_LEN);
	pos += TLS_RANDOM_LEN;
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: client_random",
		    conn->client_random, TLS_RANDOM_LEN);

	/* SessionID session_id */
	if (end - pos < 1) {
		tlsv1_server_log(conn, "Truncated ClientHello/session_id len");
		goto decode_error;
	}
	if (end - pos < 1 + *pos || *pos > TLS_SESSION_ID_MAX_LEN) {
		tlsv1_server_log(conn, "Truncated ClientHello/session_id");
		goto decode_error;
	}
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: client session_id", pos + 1, *pos);
	pos += 1 + *pos;
	/* TODO: add support for session resumption */

	/* CipherSuite cipher_suites<2..2^16-1> */
	if (end - pos < 2) {
		tlsv1_server_log(conn,
				 "Truncated ClientHello/cipher_suites len");
		goto decode_error;
	}
	num_suites = WPA_GET_BE16(pos);
	pos += 2;
	if (end - pos < num_suites) {
		tlsv1_server_log(conn, "Truncated ClientHello/cipher_suites");
		goto decode_error;
	}
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: client cipher suites",
		    pos, num_suites);
	if (num_suites & 1) {
		tlsv1_server_log(conn, "Odd len ClientHello/cipher_suites");
		goto decode_error;
	}
	num_suites /= 2;

	cipher_suite = 0;
	for (i = 0; !cipher_suite && i < conn->num_cipher_suites; i++) {
		if (testing_cipher_suite_filter(conn, conn->cipher_suites[i]))
			continue;
		c = pos;
		for (j = 0; j < num_suites; j++) {
			u16 tmp = WPA_GET_BE16(c);
			c += 2;
			if (!cipher_suite && tmp == conn->cipher_suites[i]) {
				cipher_suite = tmp;
				break;
			}
		}
	}
	pos += num_suites * 2;
	if (!cipher_suite) {
		tlsv1_server_log(conn, "No supported cipher suite available");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_ILLEGAL_PARAMETER);
		return -1;
	}

	if (tlsv1_record_set_cipher_suite(&conn->rl, cipher_suite) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to set CipherSuite for "
			   "record layer");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	conn->cipher_suite = cipher_suite;

	/* CompressionMethod compression_methods<1..2^8-1> */
	if (end - pos < 1) {
		tlsv1_server_log(conn,
				 "Truncated ClientHello/compression_methods len");
		goto decode_error;
	}
	num_suites = *pos++;
	if (end - pos < num_suites) {
		tlsv1_server_log(conn,
				 "Truncated ClientHello/compression_methods");
		goto decode_error;
	}
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: client compression_methods",
		    pos, num_suites);
	compr_null_found = 0;
	for (i = 0; i < num_suites; i++) {
		if (*pos++ == TLS_COMPRESSION_NULL)
			compr_null_found = 1;
	}
	if (!compr_null_found) {
		tlsv1_server_log(conn, "Client does not accept NULL compression");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_ILLEGAL_PARAMETER);
		return -1;
	}

	if (end - pos == 1) {
		tlsv1_server_log(conn, "Unexpected extra octet in the end of ClientHello: 0x%02x",
				 *pos);
		goto decode_error;
	}

	if (end - pos >= 2) {
		/* Extension client_hello_extension_list<0..2^16-1> */
		ext_len = WPA_GET_BE16(pos);
		pos += 2;

		tlsv1_server_log(conn, "%u bytes of ClientHello extensions",
				 ext_len);
		if (end - pos != ext_len) {
			tlsv1_server_log(conn, "Invalid ClientHello extension list length %u (expected %u)",
					 ext_len, (unsigned int) (end - pos));
			goto decode_error;
		}

		/*
		 * struct {
		 *   ExtensionType extension_type (0..65535)
		 *   opaque extension_data<0..2^16-1>
		 * } Extension;
		 */

		while (pos < end) {
			if (end - pos < 2) {
				tlsv1_server_log(conn, "Invalid extension_type field");
				goto decode_error;
			}

			ext_type = WPA_GET_BE16(pos);
			pos += 2;

			if (end - pos < 2) {
				tlsv1_server_log(conn, "Invalid extension_data length field");
				goto decode_error;
			}

			ext_len = WPA_GET_BE16(pos);
			pos += 2;

			if (end - pos < ext_len) {
				tlsv1_server_log(conn, "Invalid extension_data field");
				goto decode_error;
			}

			tlsv1_server_log(conn, "ClientHello Extension type %u",
					 ext_type);
			wpa_hexdump(MSG_MSGDUMP, "TLSv1: ClientHello "
				    "Extension data", pos, ext_len);

			if (ext_type == TLS_EXT_SESSION_TICKET) {
				os_free(conn->session_ticket);
				conn->session_ticket = os_malloc(ext_len);
				if (conn->session_ticket) {
					os_memcpy(conn->session_ticket, pos,
						  ext_len);
					conn->session_ticket_len = ext_len;
				}
			} else if (ext_type == TLS_EXT_STATUS_REQUEST) {
				conn->status_request = 1;
			} else if (ext_type == TLS_EXT_STATUS_REQUEST_V2) {
				tls_process_status_request_v2(conn, pos,
							      ext_len);
			}

			pos += ext_len;
		}
	}

	*in_len = end - in_data;

	tlsv1_server_log(conn, "ClientHello OK - proceed to ServerHello");
	conn->state = SERVER_HELLO;

	return 0;

decode_error:
	tlsv1_server_log(conn, "Failed to decode ClientHello");
	tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
			   TLS_ALERT_DECODE_ERROR);
	return -1;
}