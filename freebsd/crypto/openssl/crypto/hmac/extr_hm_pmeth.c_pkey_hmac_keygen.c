#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {TYPE_4__ ktmp; } ;
typedef  TYPE_1__ HMAC_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_OCTET_STRING_dup (TYPE_4__*) ; 
 int /*<<< orphan*/  EVP_PKEY_HMAC ; 
 int /*<<< orphan*/  EVP_PKEY_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_hmac_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    ASN1_OCTET_STRING *hkey = NULL;
    HMAC_PKEY_CTX *hctx = ctx->data;
    if (!hctx->ktmp.data)
        return 0;
    hkey = ASN1_OCTET_STRING_dup(&hctx->ktmp);
    if (!hkey)
        return 0;
    EVP_PKEY_assign(pkey, EVP_PKEY_HMAC, hkey);

    return 1;
}