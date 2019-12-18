#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* pkey; TYPE_3__* data; } ;
struct TYPE_10__ {scalar_t__ pad_mode; unsigned char const* tbuf; int /*<<< orphan*/  mgf1md; int /*<<< orphan*/  md; int /*<<< orphan*/  oaep_labellen; int /*<<< orphan*/  oaep_label; } ;
struct TYPE_8__ {int /*<<< orphan*/  rsa; } ;
struct TYPE_9__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ RSA_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY_CTX ;

/* Variables and functions */
 scalar_t__ RSA_NO_PADDING ; 
 scalar_t__ RSA_PKCS1_OAEP_PADDING ; 
 int /*<<< orphan*/  RSA_padding_add_PKCS1_OAEP_mgf1 (unsigned char const*,int,unsigned char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RSA_public_encrypt (size_t,unsigned char const*,unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int RSA_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_tbuf (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static int pkey_rsa_encrypt(EVP_PKEY_CTX *ctx,
                            unsigned char *out, size_t *outlen,
                            const unsigned char *in, size_t inlen)
{
    int ret;
    RSA_PKEY_CTX *rctx = ctx->data;

    if (rctx->pad_mode == RSA_PKCS1_OAEP_PADDING) {
        int klen = RSA_size(ctx->pkey->pkey.rsa);
        if (!setup_tbuf(rctx, ctx))
            return -1;
        if (!RSA_padding_add_PKCS1_OAEP_mgf1(rctx->tbuf, klen,
                                             in, inlen,
                                             rctx->oaep_label,
                                             rctx->oaep_labellen,
                                             rctx->md, rctx->mgf1md))
            return -1;
        ret = RSA_public_encrypt(klen, rctx->tbuf, out,
                                 ctx->pkey->pkey.rsa, RSA_NO_PADDING);
    } else {
        ret = RSA_public_encrypt(inlen, in, out, ctx->pkey->pkey.rsa,
                                 rctx->pad_mode);
    }
    if (ret < 0)
        return ret;
    *outlen = ret;
    return 1;
}