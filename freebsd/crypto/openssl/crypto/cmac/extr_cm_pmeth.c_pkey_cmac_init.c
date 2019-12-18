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
struct TYPE_3__ {scalar_t__ keygen_info_count; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * CMAC_CTX_new () ; 

__attribute__((used)) static int pkey_cmac_init(EVP_PKEY_CTX *ctx)
{
    ctx->data = CMAC_CTX_new();
    if (ctx->data == NULL)
        return 0;
    ctx->keygen_info_count = 0;
    return 1;
}