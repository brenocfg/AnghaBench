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
struct TYPE_4__ {scalar_t__ num; int /*<<< orphan*/  enc_data; } ;
typedef  TYPE_1__ EVP_ENCODE_CTX ;

/* Variables and functions */
 int evp_decodeblock_int (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 

int EVP_DecodeFinal(EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl)
{
    int i;

    *outl = 0;
    if (ctx->num != 0) {
        i = evp_decodeblock_int(ctx, out, ctx->enc_data, ctx->num);
        if (i < 0)
            return -1;
        ctx->num = 0;
        *outl = i;
        return 1;
    } else
        return 1;
}