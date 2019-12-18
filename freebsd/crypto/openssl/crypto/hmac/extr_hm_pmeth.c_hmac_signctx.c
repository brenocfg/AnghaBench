#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ HMAC_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int EVP_MD_CTX_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ ,unsigned char*,unsigned int*) ; 

__attribute__((used)) static int hmac_signctx(EVP_PKEY_CTX *ctx, unsigned char *sig, size_t *siglen,
                        EVP_MD_CTX *mctx)
{
    unsigned int hlen;
    HMAC_PKEY_CTX *hctx = ctx->data;
    int l = EVP_MD_CTX_size(mctx);

    if (l < 0)
        return 0;
    *siglen = l;
    if (!sig)
        return 1;

    if (!HMAC_Final(hctx->ctx, sig, &hlen))
        return 0;
    *siglen = (size_t)hlen;
    return 1;
}