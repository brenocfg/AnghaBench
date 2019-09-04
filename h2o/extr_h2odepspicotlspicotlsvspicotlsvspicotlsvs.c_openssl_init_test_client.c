#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  super; } ;
typedef  TYPE_1__ ptls_openssl_verify_certificate_t ;
struct TYPE_7__ {int /*<<< orphan*/ * verify_certificate; int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/  key_exchanges; int /*<<< orphan*/ * get_time; int /*<<< orphan*/  random_bytes; } ;
typedef  TYPE_2__ ptls_context_t ;
typedef  int /*<<< orphan*/  X509_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openssl_init_cert_store (char const*) ; 
 int /*<<< orphan*/  ptls_get_time ; 
 int /*<<< orphan*/  ptls_openssl_cipher_suites ; 
 int /*<<< orphan*/  ptls_openssl_init_verify_certificate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_openssl_key_exchanges ; 
 int /*<<< orphan*/  ptls_openssl_random_bytes ; 

int openssl_init_test_client(ptls_context_t *ctx_client, char const * crt_file)
{
	int ret = 0;
	static ptls_openssl_verify_certificate_t verifier;
    X509_STORE *store = NULL;

	/* Initialize the client context */
	memset(ctx_client, 0, sizeof(ptls_context_t));
	ctx_client->random_bytes = ptls_openssl_random_bytes;
    ctx_client->get_time = &ptls_get_time;
	ctx_client->key_exchanges = ptls_openssl_key_exchanges;
	ctx_client->cipher_suites = ptls_openssl_cipher_suites;
	ptls_openssl_init_verify_certificate(&verifier, openssl_init_cert_store(crt_file));
	ctx_client->verify_certificate = &verifier.super;

	return ret;
}