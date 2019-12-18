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
struct qcom_rng_ctx {struct qcom_rng* rng; } ;
struct qcom_rng {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; } ;
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct qcom_rng_ctx* crypto_rng_ctx (struct crypto_rng*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qcom_rng_read (struct qcom_rng*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int qcom_rng_generate(struct crypto_rng *tfm,
			     const u8 *src, unsigned int slen,
			     u8 *dstn, unsigned int dlen)
{
	struct qcom_rng_ctx *ctx = crypto_rng_ctx(tfm);
	struct qcom_rng *rng = ctx->rng;
	int ret;

	ret = clk_prepare_enable(rng->clk);
	if (ret)
		return ret;

	mutex_lock(&rng->lock);

	ret = qcom_rng_read(rng, dstn, dlen);

	mutex_unlock(&rng->lock);
	clk_disable_unprepare(rng->clk);

	return 0;
}