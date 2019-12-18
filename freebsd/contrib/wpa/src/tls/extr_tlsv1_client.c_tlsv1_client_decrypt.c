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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct tlsv1_client {struct wpabuf* partial_input; int /*<<< orphan*/  rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ TLS_ALERT_DECODE_ERROR ; 
 scalar_t__ TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 scalar_t__ TLS_ALERT_LEVEL_WARNING ; 
 scalar_t__ TLS_ALERT_UNEXPECTED_MESSAGE ; 
 scalar_t__ TLS_CONTENT_TYPE_ALERT ; 
 scalar_t__ TLS_CONTENT_TYPE_APPLICATION_DATA ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,scalar_t__) ; 
 int tlsv1_record_receive (int /*<<< orphan*/ *,scalar_t__ const*,int,scalar_t__*,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc_copy (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__* wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 scalar_t__* wpabuf_put (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__ const*,size_t) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,int) ; 
 size_t wpabuf_tailroom (struct wpabuf*) ; 

struct wpabuf * tlsv1_client_decrypt(struct tlsv1_client *conn,
				     const u8 *in_data, size_t in_len,
				     int *need_more_data)
{
	const u8 *in_end, *pos;
	int used;
	u8 alert, *out_pos, ct;
	size_t olen;
	struct wpabuf *buf = NULL;

	if (need_more_data)
		*need_more_data = 0;

	if (conn->partial_input) {
		if (wpabuf_resize(&conn->partial_input, in_len) < 0) {
			wpa_printf(MSG_DEBUG, "TLSv1: Failed to allocate "
				   "memory for pending record");
			alert = TLS_ALERT_INTERNAL_ERROR;
			goto fail;
		}
		wpabuf_put_data(conn->partial_input, in_data, in_len);
		in_data = wpabuf_head(conn->partial_input);
		in_len = wpabuf_len(conn->partial_input);
	}

	pos = in_data;
	in_end = in_data + in_len;

	while (pos < in_end) {
		ct = pos[0];
		if (wpabuf_resize(&buf, in_end - pos) < 0) {
			alert = TLS_ALERT_INTERNAL_ERROR;
			goto fail;
		}
		out_pos = wpabuf_put(buf, 0);
		olen = wpabuf_tailroom(buf);
		used = tlsv1_record_receive(&conn->rl, pos, in_end - pos,
					    out_pos, &olen, &alert);
		if (used < 0) {
			wpa_printf(MSG_DEBUG, "TLSv1: Record layer processing "
				   "failed");
			goto fail;
		}
		if (used == 0) {
			struct wpabuf *partial;
			wpa_printf(MSG_DEBUG, "TLSv1: Need more data");
			partial = wpabuf_alloc_copy(pos, in_end - pos);
			wpabuf_free(conn->partial_input);
			conn->partial_input = partial;
			if (conn->partial_input == NULL) {
				wpa_printf(MSG_DEBUG, "TLSv1: Failed to "
					   "allocate memory for pending "
					   "record");
				alert = TLS_ALERT_INTERNAL_ERROR;
				goto fail;
			}
			if (need_more_data)
				*need_more_data = 1;
			return buf;
		}

		if (ct == TLS_CONTENT_TYPE_ALERT) {
			if (olen < 2) {
				wpa_printf(MSG_DEBUG, "TLSv1: Alert "
					   "underflow");
				alert = TLS_ALERT_DECODE_ERROR;
				goto fail;
			}
			wpa_printf(MSG_DEBUG, "TLSv1: Received alert %d:%d",
				   out_pos[0], out_pos[1]);
			if (out_pos[0] == TLS_ALERT_LEVEL_WARNING) {
				/* Continue processing */
				pos += used;
				continue;
			}

			alert = out_pos[1];
			goto fail;
		}

		if (ct != TLS_CONTENT_TYPE_APPLICATION_DATA) {
			wpa_printf(MSG_DEBUG, "TLSv1: Unexpected content type "
				   "0x%x when decrypting application data",
				   pos[0]);
			alert = TLS_ALERT_UNEXPECTED_MESSAGE;
			goto fail;
		}

		wpabuf_put(buf, olen);

		pos += used;
	}

	wpabuf_free(conn->partial_input);
	conn->partial_input = NULL;
	return buf;

fail:
	wpabuf_free(buf);
	wpabuf_free(conn->partial_input);
	conn->partial_input = NULL;
	tls_alert(conn, TLS_ALERT_LEVEL_FATAL, alert);
	return NULL;
}