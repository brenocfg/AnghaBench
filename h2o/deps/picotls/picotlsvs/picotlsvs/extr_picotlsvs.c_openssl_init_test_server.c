#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/  key_exchanges; int /*<<< orphan*/ * get_time; int /*<<< orphan*/  random_bytes; } ;
typedef  TYPE_1__ ptls_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetSignCertificate (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptls_get_time ; 
 int ptls_load_certificates (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  ptls_openssl_cipher_suites ; 
 int /*<<< orphan*/  ptls_openssl_key_exchanges ; 
 int /*<<< orphan*/  ptls_openssl_random_bytes ; 
 int /*<<< orphan*/  stderr ; 

int openssl_init_test_server(ptls_context_t *ctx_server, 
    char const * key_file, char const * cert_file)
{
	int ret = 0;
	/* Initialize the server context */
	memset(ctx_server, 0, sizeof(ptls_context_t));
	ctx_server->random_bytes = ptls_openssl_random_bytes;
    ctx_server->get_time = &ptls_get_time;
	ctx_server->key_exchanges = ptls_openssl_key_exchanges;
	ctx_server->cipher_suites = ptls_openssl_cipher_suites;

	ret = ptls_load_certificates(ctx_server, cert_file);
	if (ret != 0)
	{
		fprintf(stderr, "Could not read the server certificates\n");
	}
	else
	{
		SetSignCertificate(key_file, ctx_server);
	}

	return ret;
}