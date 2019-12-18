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
struct TYPE_4__ {int nlast_block; int /*<<< orphan*/  last_block; int /*<<< orphan*/  tbl; int /*<<< orphan*/  k2; int /*<<< orphan*/  k1; int /*<<< orphan*/  cctx; } ;
typedef  TYPE_1__ CMAC_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int CMAC_CTX_copy(CMAC_CTX *out, const CMAC_CTX *in)
{
    int bl;
    if (in->nlast_block == -1)
        return 0;
    if (!EVP_CIPHER_CTX_copy(out->cctx, in->cctx))
        return 0;
    bl = EVP_CIPHER_CTX_block_size(in->cctx);
    memcpy(out->k1, in->k1, bl);
    memcpy(out->k2, in->k2, bl);
    memcpy(out->tbl, in->tbl, bl);
    memcpy(out->last_block, in->last_block, bl);
    out->nlast_block = in->nlast_block;
    return 1;
}