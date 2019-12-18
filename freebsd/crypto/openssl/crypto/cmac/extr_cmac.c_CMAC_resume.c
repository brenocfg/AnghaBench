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
struct TYPE_3__ {int nlast_block; int /*<<< orphan*/  tbl; int /*<<< orphan*/  cctx; } ;
typedef  TYPE_1__ CMAC_CTX ;

/* Variables and functions */
 int EVP_EncryptInit_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int CMAC_resume(CMAC_CTX *ctx)
{
    if (ctx->nlast_block == -1)
        return 0;
    /*
     * The buffer "tbl" contains the last fully encrypted block which is the
     * last IV (or all zeroes if no last encrypted block). The last block has
     * not been modified since CMAC_final(). So reinitialising using the last
     * decrypted block will allow CMAC to continue after calling
     * CMAC_Final().
     */
    return EVP_EncryptInit_ex(ctx->cctx, NULL, NULL, NULL, ctx->tbl);
}