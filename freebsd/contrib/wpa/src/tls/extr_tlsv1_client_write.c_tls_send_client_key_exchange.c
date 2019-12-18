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
struct tlsv1_client {int /*<<< orphan*/  state; TYPE_1__* cred; scalar_t__ certificate_requested; } ;
struct TYPE_2__ {scalar_t__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERVER_CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 scalar_t__ tls_client_cert_chain_der_len (struct tlsv1_client*) ; 
 scalar_t__ tls_write_client_certificate (struct tlsv1_client*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_client_certificate_verify (struct tlsv1_client*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_client_change_cipher_spec (struct tlsv1_client*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_client_finished (struct tlsv1_client*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_write_client_key_exchange (struct tlsv1_client*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 * tls_send_client_key_exchange(struct tlsv1_client *conn,
					 size_t *out_len)
{
	u8 *msg, *end, *pos;
	size_t msglen;

	*out_len = 0;

	msglen = 2000;
	if (conn->certificate_requested)
		msglen += tls_client_cert_chain_der_len(conn);

	msg = os_malloc(msglen);
	if (msg == NULL)
		return NULL;

	pos = msg;
	end = msg + msglen;

	if (conn->certificate_requested) {
		if (tls_write_client_certificate(conn, &pos, end) < 0) {
			os_free(msg);
			return NULL;
		}
	}

	if (tls_write_client_key_exchange(conn, &pos, end) < 0 ||
	    (conn->certificate_requested && conn->cred && conn->cred->key &&
	     tls_write_client_certificate_verify(conn, &pos, end) < 0) ||
	    tls_write_client_change_cipher_spec(conn, &pos, end) < 0 ||
	    tls_write_client_finished(conn, &pos, end) < 0) {
		os_free(msg);
		return NULL;
	}

	*out_len = pos - msg;

	conn->state = SERVER_CHANGE_CIPHER_SPEC;

	return msg;
}