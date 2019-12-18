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
typedef  unsigned int u32 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct md5_hmac_ctx {int byte_count; char* block; } ;

/* Variables and functions */
 struct md5_hmac_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md5_hmac_transform (struct shash_desc*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,unsigned int const) ; 

__attribute__((used)) static int md5_hmac_update(struct shash_desc *desc, const u8 *data, unsigned int len)
{
    struct md5_hmac_ctx *mctx = crypto_shash_ctx(desc->tfm);
    const u32 avail = sizeof(mctx->block) - (mctx->byte_count & 0x3f);

    mctx->byte_count += len;
    
    if (avail > len) {
        memcpy((char *)mctx->block + (sizeof(mctx->block) - avail),
               data, len);
        return 0;
    }

    memcpy((char *)mctx->block + (sizeof(mctx->block) - avail),
           data, avail);

    md5_hmac_transform(desc, mctx->block);
    data += avail;
    len -= avail;

    while (len >= sizeof(mctx->block)) {
        memcpy(mctx->block, data, sizeof(mctx->block));
        md5_hmac_transform(desc, mctx->block);
        data += sizeof(mctx->block);
        len -= sizeof(mctx->block);
    }

    memcpy(mctx->block, data, len);
    return 0;    
}