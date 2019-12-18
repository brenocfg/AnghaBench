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
struct tlsv1_server {scalar_t__ dh_secret_len; int /*<<< orphan*/ * dh_secret; scalar_t__ use_session_ticket; scalar_t__ session_ticket_len; int /*<<< orphan*/ * session_ticket; int /*<<< orphan*/ * client_rsa_key; int /*<<< orphan*/  verify; int /*<<< orphan*/  rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_NULL_WITH_NULL_NULL ; 
 int /*<<< orphan*/  crypto_public_key_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_verify_hash_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_record_change_read_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_record_change_write_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_record_set_cipher_suite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tlsv1_server_clear_data(struct tlsv1_server *conn)
{
	tlsv1_record_set_cipher_suite(&conn->rl, TLS_NULL_WITH_NULL_NULL);
	tlsv1_record_change_write_cipher(&conn->rl);
	tlsv1_record_change_read_cipher(&conn->rl);
	tls_verify_hash_free(&conn->verify);

	crypto_public_key_free(conn->client_rsa_key);
	conn->client_rsa_key = NULL;

	os_free(conn->session_ticket);
	conn->session_ticket = NULL;
	conn->session_ticket_len = 0;
	conn->use_session_ticket = 0;

	os_free(conn->dh_secret);
	conn->dh_secret = NULL;
	conn->dh_secret_len = 0;
}