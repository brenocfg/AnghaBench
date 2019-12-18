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
typedef  int /*<<< orphan*/  u32 ;
struct s5p_hash_reqctx {unsigned int nregs; scalar_t__ digest; } ;
struct s5p_aes_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSS_REG_HASH_IV (unsigned int) ; 
 int /*<<< orphan*/  s5p_hash_write (struct s5p_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void s5p_hash_write_ctx_iv(struct s5p_aes_dev *dd,
				  const struct s5p_hash_reqctx *ctx)
{
	const u32 *hash = (const u32 *)ctx->digest;
	unsigned int i;

	for (i = 0; i < ctx->nregs; i++)
		s5p_hash_write(dd, SSS_REG_HASH_IV(i), hash[i]);
}