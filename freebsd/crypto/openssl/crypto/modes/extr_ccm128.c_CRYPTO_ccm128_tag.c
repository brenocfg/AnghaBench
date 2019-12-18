#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  c; } ;
struct TYPE_5__ {int* c; } ;
struct TYPE_7__ {TYPE_2__ cmac; TYPE_1__ nonce; } ;
typedef  TYPE_3__ CCM128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

size_t CRYPTO_ccm128_tag(CCM128_CONTEXT *ctx, unsigned char *tag, size_t len)
{
    unsigned int M = (ctx->nonce.c[0] >> 3) & 7; /* the M parameter */

    M *= 2;
    M += 2;
    if (len != M)
        return 0;
    memcpy(tag, ctx->cmac.c, M);
    return M;
}