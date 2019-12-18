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
struct tlsv1_client {int state; } ;

/* Variables and functions */
#define  ACK_FINISHED 130 
#define  CHANGE_CIPHER_SPEC 129 
#define  CLIENT_KEY_EXCHANGE 128 
 int ESTABLISHED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/ * tls_send_change_cipher_spec (struct tlsv1_client*,size_t*) ; 
 int /*<<< orphan*/ * tls_send_client_key_exchange (struct tlsv1_client*,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

u8 * tlsv1_client_handshake_write(struct tlsv1_client *conn, size_t *out_len,
				  int no_appl_data)
{
	switch (conn->state) {
	case CLIENT_KEY_EXCHANGE:
		return tls_send_client_key_exchange(conn, out_len);
	case CHANGE_CIPHER_SPEC:
		return tls_send_change_cipher_spec(conn, out_len);
	case ACK_FINISHED:
		wpa_printf(MSG_DEBUG, "TLSv1: Handshake completed "
			   "successfully");
		conn->state = ESTABLISHED;
		*out_len = 0;
		if (no_appl_data) {
			/* Need to return something to get final TLS ACK. */
			return os_malloc(1);
		}
		return NULL;
	default:
		wpa_printf(MSG_DEBUG, "TLSv1: Unexpected state %d while "
			   "generating reply", conn->state);
		return NULL;
	}
}