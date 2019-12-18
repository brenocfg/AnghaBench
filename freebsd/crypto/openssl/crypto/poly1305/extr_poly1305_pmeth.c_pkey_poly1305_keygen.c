#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ktmp; } ;
typedef  TYPE_1__ POLY1305_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_OCTET_STRING_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_assign_POLY1305 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_poly1305_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    ASN1_OCTET_STRING *key;
    POLY1305_PKEY_CTX *pctx = EVP_PKEY_CTX_get_data(ctx);

    if (ASN1_STRING_get0_data(&pctx->ktmp) == NULL)
        return 0;
    key = ASN1_OCTET_STRING_dup(&pctx->ktmp);
    if (key == NULL)
        return 0;
    return EVP_PKEY_assign_POLY1305(pkey, key);
}