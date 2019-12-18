#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* data; TYPE_2__* pkey; } ;
struct TYPE_8__ {int /*<<< orphan*/ * md; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ec; } ;
struct TYPE_7__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ SM2_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_sm3 () ; 
 int sm2_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char const*,size_t,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  sm2_plaintext_size (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,size_t*) ; 

__attribute__((used)) static int pkey_sm2_decrypt(EVP_PKEY_CTX *ctx,
                            unsigned char *out, size_t *outlen,
                            const unsigned char *in, size_t inlen)
{
    EC_KEY *ec = ctx->pkey->pkey.ec;
    SM2_PKEY_CTX *dctx = ctx->data;
    const EVP_MD *md = (dctx->md == NULL) ? EVP_sm3() : dctx->md;

    if (out == NULL) {
        if (!sm2_plaintext_size(ec, md, inlen, outlen))
            return -1;
        else
            return 1;
    }

    return sm2_decrypt(ec, md, in, inlen, out, outlen);
}