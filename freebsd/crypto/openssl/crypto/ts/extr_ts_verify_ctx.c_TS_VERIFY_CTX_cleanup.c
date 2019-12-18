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
struct TYPE_4__ {int /*<<< orphan*/  tsa_name; int /*<<< orphan*/  nonce; int /*<<< orphan*/  data; int /*<<< orphan*/  imprint; int /*<<< orphan*/  md_alg; int /*<<< orphan*/  policy; int /*<<< orphan*/  certs; int /*<<< orphan*/  store; } ;
typedef  TYPE_1__ TS_VERIFY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERAL_NAME_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_VERIFY_CTX_init (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_ALGOR_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void TS_VERIFY_CTX_cleanup(TS_VERIFY_CTX *ctx)
{
    if (!ctx)
        return;

    X509_STORE_free(ctx->store);
    sk_X509_pop_free(ctx->certs, X509_free);

    ASN1_OBJECT_free(ctx->policy);

    X509_ALGOR_free(ctx->md_alg);
    OPENSSL_free(ctx->imprint);

    BIO_free_all(ctx->data);

    ASN1_INTEGER_free(ctx->nonce);

    GENERAL_NAME_free(ctx->tsa_name);

    TS_VERIFY_CTX_init(ctx);
}