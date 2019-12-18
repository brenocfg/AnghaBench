#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_2__* pkey; TYPE_3__* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_7__ {scalar_t__ ptr; } ;
struct TYPE_8__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ POLY1305_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_5__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_NO_INIT ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_update_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ POLY1305_KEY_SIZE ; 
 int /*<<< orphan*/  Poly1305_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_update ; 

__attribute__((used)) static int poly1305_signctx_init(EVP_PKEY_CTX *ctx, EVP_MD_CTX *mctx)
{
    POLY1305_PKEY_CTX *pctx = ctx->data;
    ASN1_OCTET_STRING *key = (ASN1_OCTET_STRING *)ctx->pkey->pkey.ptr;

    if (key->length != POLY1305_KEY_SIZE)
        return 0;
    EVP_MD_CTX_set_flags(mctx, EVP_MD_CTX_FLAG_NO_INIT);
    EVP_MD_CTX_set_update_fn(mctx, int_update);
    Poly1305_Init(&pctx->ctx, key->data);
    return 1;
}