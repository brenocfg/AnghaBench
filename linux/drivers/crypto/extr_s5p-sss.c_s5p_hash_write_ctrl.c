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
typedef  int u64 ;
typedef  int u32 ;
struct s5p_hash_reqctx {int engine; int digcnt; } ;
struct s5p_aes_dev {int /*<<< orphan*/  hash_req; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SSS_HASH_BYTESWAP_DI ; 
 int SSS_HASH_BYTESWAP_DO ; 
 int SSS_HASH_BYTESWAP_IV ; 
 int SSS_HASH_BYTESWAP_KEY ; 
 int SSS_HASH_INIT_BIT ; 
 int SSS_HASH_USER_IV_EN ; 
 int /*<<< orphan*/  SSS_REG_HASH_CTRL ; 
 int /*<<< orphan*/  SSS_REG_HASH_CTRL_SWAP ; 
 int /*<<< orphan*/  SSS_REG_HASH_MSG_SIZE_HIGH ; 
 int /*<<< orphan*/  SSS_REG_HASH_MSG_SIZE_LOW ; 
 int /*<<< orphan*/  SSS_REG_HASH_PRE_MSG_SIZE_HIGH ; 
 int /*<<< orphan*/  SSS_REG_HASH_PRE_MSG_SIZE_LOW ; 
 struct s5p_hash_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  s5p_hash_write (struct s5p_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5p_hash_write_ctx_iv (struct s5p_aes_dev*,struct s5p_hash_reqctx*) ; 

__attribute__((used)) static void s5p_hash_write_ctrl(struct s5p_aes_dev *dd, size_t length,
				bool final)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(dd->hash_req);
	u32 prelow, prehigh, low, high;
	u32 configflags, swapflags;
	u64 tmplen;

	configflags = ctx->engine | SSS_HASH_INIT_BIT;

	if (likely(ctx->digcnt)) {
		s5p_hash_write_ctx_iv(dd, ctx);
		configflags |= SSS_HASH_USER_IV_EN;
	}

	if (final) {
		/* number of bytes for last part */
		low = length;
		high = 0;
		/* total number of bits prev hashed */
		tmplen = ctx->digcnt * 8;
		prelow = (u32)tmplen;
		prehigh = (u32)(tmplen >> 32);
	} else {
		prelow = 0;
		prehigh = 0;
		low = 0;
		high = BIT(31);
	}

	swapflags = SSS_HASH_BYTESWAP_DI | SSS_HASH_BYTESWAP_DO |
		    SSS_HASH_BYTESWAP_IV | SSS_HASH_BYTESWAP_KEY;

	s5p_hash_write(dd, SSS_REG_HASH_MSG_SIZE_LOW, low);
	s5p_hash_write(dd, SSS_REG_HASH_MSG_SIZE_HIGH, high);
	s5p_hash_write(dd, SSS_REG_HASH_PRE_MSG_SIZE_LOW, prelow);
	s5p_hash_write(dd, SSS_REG_HASH_PRE_MSG_SIZE_HIGH, prehigh);

	s5p_hash_write(dd, SSS_REG_HASH_CTRL_SWAP, swapflags);
	s5p_hash_write(dd, SSS_REG_HASH_CTRL, configflags);
}