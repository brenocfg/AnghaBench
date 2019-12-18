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
struct s5p_hash_reqctx {unsigned int nregs; scalar_t__ digest; struct s5p_aes_dev* dd; } ;
struct s5p_aes_dev {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSS_REG_HASH_OUT (unsigned int) ; 
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  s5p_hash_read (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_hash_read_msg(struct ahash_request *req)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	struct s5p_aes_dev *dd = ctx->dd;
	u32 *hash = (u32 *)ctx->digest;
	unsigned int i;

	for (i = 0; i < ctx->nregs; i++)
		hash[i] = s5p_hash_read(dd, SSS_REG_HASH_OUT(i));
}