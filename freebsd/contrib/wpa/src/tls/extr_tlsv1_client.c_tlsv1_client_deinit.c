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
struct tlsv1_client {int /*<<< orphan*/  server_cert; int /*<<< orphan*/  partial_input; int /*<<< orphan*/  cred; struct tlsv1_client* client_hello_ext; int /*<<< orphan*/  verify; int /*<<< orphan*/  rl; int /*<<< orphan*/  server_rsa_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_NULL_WITH_NULL_NULL ; 
 int /*<<< orphan*/  crypto_public_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct tlsv1_client*) ; 
 int /*<<< orphan*/  tls_verify_hash_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_client_free_dh (struct tlsv1_client*) ; 
 int /*<<< orphan*/  tlsv1_cred_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_record_change_read_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_record_change_write_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_record_set_cipher_suite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x509_certificate_chain_free (int /*<<< orphan*/ ) ; 

void tlsv1_client_deinit(struct tlsv1_client *conn)
{
	crypto_public_key_free(conn->server_rsa_key);
	tlsv1_record_set_cipher_suite(&conn->rl, TLS_NULL_WITH_NULL_NULL);
	tlsv1_record_change_write_cipher(&conn->rl);
	tlsv1_record_change_read_cipher(&conn->rl);
	tls_verify_hash_free(&conn->verify);
	os_free(conn->client_hello_ext);
	tlsv1_client_free_dh(conn);
	tlsv1_cred_free(conn->cred);
	wpabuf_free(conn->partial_input);
	x509_certificate_chain_free(conn->server_cert);
	os_free(conn);
}