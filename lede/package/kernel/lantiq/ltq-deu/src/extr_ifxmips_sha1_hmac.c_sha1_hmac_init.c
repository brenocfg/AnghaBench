#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct sha1_hmac_ctx {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; scalar_t__ dbn; } ;

/* Variables and functions */
 struct sha1_hmac_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha1_hmac_setkey_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sha1_hmac_init(struct shash_desc *desc)
{
    struct sha1_hmac_ctx *sctx =  crypto_shash_ctx(desc->tfm);

    //printk("debug ln: %d, fn: %s\n", __LINE__, __func__);
    sctx->dbn = 0; //dbn workaround
    sha1_hmac_setkey_hw(sctx->key, sctx->keylen);

    return 0;
}