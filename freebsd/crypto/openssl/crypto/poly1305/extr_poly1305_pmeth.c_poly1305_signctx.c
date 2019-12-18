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
typedef  TYPE_1__ POLY1305_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 size_t POLY1305_DIGEST_SIZE ; 
 int /*<<< orphan*/  Poly1305_Final (int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int poly1305_signctx(EVP_PKEY_CTX *ctx, unsigned char *sig, size_t *siglen,
                            EVP_MD_CTX *mctx)
{
    POLY1305_PKEY_CTX *pctx = ctx->data;

    *siglen = POLY1305_DIGEST_SIZE;
    if (sig != NULL)
        Poly1305_Final(&pctx->ctx, sig);
    return 1;
}