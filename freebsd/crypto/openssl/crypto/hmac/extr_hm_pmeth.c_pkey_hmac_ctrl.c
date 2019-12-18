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
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  engine; TYPE_2__* pkey; TYPE_3__* data; } ;
struct TYPE_9__ {void* md; int /*<<< orphan*/  ctx; int /*<<< orphan*/  ktmp; } ;
struct TYPE_7__ {scalar_t__ ptr; } ;
struct TYPE_8__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ HMAC_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY_CTX ;
typedef  TYPE_5__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,void*,int) ; 
#define  EVP_PKEY_CTRL_DIGESTINIT 130 
#define  EVP_PKEY_CTRL_MD 129 
#define  EVP_PKEY_CTRL_SET_MAC_KEY 128 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkey_hmac_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    HMAC_PKEY_CTX *hctx = ctx->data;
    ASN1_OCTET_STRING *key;
    switch (type) {

    case EVP_PKEY_CTRL_SET_MAC_KEY:
        if ((!p2 && p1 > 0) || (p1 < -1))
            return 0;
        if (!ASN1_OCTET_STRING_set(&hctx->ktmp, p2, p1))
            return 0;
        break;

    case EVP_PKEY_CTRL_MD:
        hctx->md = p2;
        break;

    case EVP_PKEY_CTRL_DIGESTINIT:
        key = (ASN1_OCTET_STRING *)ctx->pkey->pkey.ptr;
        if (!HMAC_Init_ex(hctx->ctx, key->data, key->length, hctx->md,
                          ctx->engine))
            return 0;
        break;

    default:
        return -2;

    }
    return 1;
}