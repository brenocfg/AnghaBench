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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct sha1_hmac_ctx {int count; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 struct sha1_hmac_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  sha1_hmac_transform (struct shash_desc*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int sha1_hmac_update(struct shash_desc *desc, const u8 *data,
            unsigned int len)
{
    struct sha1_hmac_ctx *sctx =  crypto_shash_ctx(desc->tfm);
    unsigned int i, j;

    j = (sctx->count >> 3) & 0x3f;
    sctx->count += len << 3;
   // printk("sctx->count = %d\n", sctx->count);

    if ((j + len) > 63) {
        memcpy (&sctx->buffer[j], data, (i = 64 - j));
        sha1_hmac_transform (desc, (const u32 *)sctx->buffer);
        for (; i + 63 < len; i += 64) {
            sha1_hmac_transform (desc, (const u32 *)&data[i]);
        }

        j = 0;
    }
    else
        i = 0;

    memcpy (&sctx->buffer[j], &data[i], len - i);
    return 0;
}