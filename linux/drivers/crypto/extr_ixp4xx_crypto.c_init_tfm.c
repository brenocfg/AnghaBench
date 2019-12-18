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
struct ixp_ctx {int /*<<< orphan*/  encrypt; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  configuring; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ixp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  free_sa_dir (int /*<<< orphan*/ *) ; 
 int init_sa_dir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_tfm(struct crypto_tfm *tfm)
{
	struct ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	int ret;

	atomic_set(&ctx->configuring, 0);
	ret = init_sa_dir(&ctx->encrypt);
	if (ret)
		return ret;
	ret = init_sa_dir(&ctx->decrypt);
	if (ret) {
		free_sa_dir(&ctx->encrypt);
	}
	return ret;
}