#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * verify_certificate; int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/  key_exchanges; int /*<<< orphan*/ * get_time; int /*<<< orphan*/  random_bytes; } ;
typedef  TYPE_1__ ptls_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptls_get_time ; 
 int /*<<< orphan*/  ptls_minicrypto_cipher_suites ; 
 int /*<<< orphan*/  ptls_minicrypto_key_exchanges ; 
 int /*<<< orphan*/  ptls_minicrypto_random_bytes ; 

int minicrypto_init_test_client(ptls_context_t *ctx_client)
{
	int ret = 0;
	/* Initialize the client context */
	memset(ctx_client, 0, sizeof(ptls_context_t));
	ctx_client->random_bytes = ptls_minicrypto_random_bytes;
    ctx_client->get_time = &ptls_get_time;
	ctx_client->key_exchanges = ptls_minicrypto_key_exchanges;
	ctx_client->cipher_suites = ptls_minicrypto_cipher_suites;
	ctx_client->verify_certificate = NULL; // &verifier.super;

	return ret;
}