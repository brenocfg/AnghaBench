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
struct tlsv1_client {scalar_t__ state; struct wpabuf* partial_input; int /*<<< orphan*/  alert_description; scalar_t__ alert_level; int /*<<< orphan*/  rl; } ;

/* Variables and functions */
 scalar_t__ CLIENT_HELLO ; 
 scalar_t__ FAILED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/ * os_zalloc (int) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tls_send_client_hello (struct tlsv1_client*,size_t*) ; 
 int /*<<< orphan*/ * tlsv1_client_handshake_write (struct tlsv1_client*,size_t*,int) ; 
 scalar_t__ tlsv1_client_process_handshake (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/ * tlsv1_client_send_alert (struct tlsv1_client*,scalar_t__,int /*<<< orphan*/ ,size_t*) ; 
 int tlsv1_record_receive (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,size_t) ; 

u8 * tlsv1_client_handshake(struct tlsv1_client *conn,
			    const u8 *in_data, size_t in_len,
			    size_t *out_len, u8 **appl_data,
			    size_t *appl_data_len, int *need_more_data)
{
	const u8 *pos, *end;
	u8 *msg = NULL, *in_msg = NULL, *in_pos, *in_end, alert, ct;
	size_t in_msg_len;
	int no_appl_data;
	int used;

	if (need_more_data)
		*need_more_data = 0;

	if (conn->state == CLIENT_HELLO) {
		if (in_len)
			return NULL;
		return tls_send_client_hello(conn, out_len);
	}

	if (conn->partial_input) {
		if (wpabuf_resize(&conn->partial_input, in_len) < 0) {
			wpa_printf(MSG_DEBUG, "TLSv1: Failed to allocate "
				   "memory for pending record");
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
				  TLS_ALERT_INTERNAL_ERROR);
			goto failed;
		}
		wpabuf_put_data(conn->partial_input, in_data, in_len);
		in_data = wpabuf_head(conn->partial_input);
		in_len = wpabuf_len(conn->partial_input);
	}

	if (in_data == NULL || in_len == 0)
		return NULL;

	pos = in_data;
	end = in_data + in_len;
	in_msg = os_malloc(in_len);
	if (in_msg == NULL)
		return NULL;

	/* Each received packet may include multiple records */
	while (pos < end) {
		in_msg_len = in_len;
		used = tlsv1_record_receive(&conn->rl, pos, end - pos,
					    in_msg, &in_msg_len, &alert);
		if (used < 0) {
			wpa_printf(MSG_DEBUG, "TLSv1: Processing received "
				   "record failed");
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL, alert);
			goto failed;
		}
		if (used == 0) {
			struct wpabuf *partial;
			wpa_printf(MSG_DEBUG, "TLSv1: Need more data");
			partial = wpabuf_alloc_copy(pos, end - pos);
			wpabuf_free(conn->partial_input);
			conn->partial_input = partial;
			if (conn->partial_input == NULL) {
				wpa_printf(MSG_DEBUG, "TLSv1: Failed to "
					   "allocate memory for pending "
					   "record");
				tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
					  TLS_ALERT_INTERNAL_ERROR);
				goto failed;
			}
			os_free(in_msg);
			if (need_more_data)
				*need_more_data = 1;
			return NULL;
		}
		ct = pos[0];

		in_pos = in_msg;
		in_end = in_msg + in_msg_len;

		/* Each received record may include multiple messages of the
		 * same ContentType. */
		while (in_pos < in_end) {
			in_msg_len = in_end - in_pos;
			if (tlsv1_client_process_handshake(conn, ct, in_pos,
							   &in_msg_len,
							   appl_data,
							   appl_data_len) < 0)
				goto failed;
			in_pos += in_msg_len;
		}

		pos += used;
	}

	os_free(in_msg);
	in_msg = NULL;

	no_appl_data = appl_data == NULL || *appl_data == NULL;
	msg = tlsv1_client_handshake_write(conn, out_len, no_appl_data);

failed:
	os_free(in_msg);
	if (conn->alert_level) {
		wpabuf_free(conn->partial_input);
		conn->partial_input = NULL;
		conn->state = FAILED;
		os_free(msg);
		msg = tlsv1_client_send_alert(conn, conn->alert_level,
					      conn->alert_description,
					      out_len);
	} else if (msg == NULL) {
		msg = os_zalloc(1);
		*out_len = 0;
	}

	if (need_more_data == NULL || !(*need_more_data)) {
		wpabuf_free(conn->partial_input);
		conn->partial_input = NULL;
	}

	return msg;
}