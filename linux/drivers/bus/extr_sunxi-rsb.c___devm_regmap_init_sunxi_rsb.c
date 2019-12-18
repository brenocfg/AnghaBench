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
struct sunxi_rsb_device {int /*<<< orphan*/  dev; } ;
struct sunxi_rsb_ctx {int dummy; } ;
struct regmap_config {int dummy; } ;
struct regmap {int dummy; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 struct regmap* ERR_CAST (struct sunxi_rsb_ctx*) ; 
 scalar_t__ IS_ERR (struct sunxi_rsb_ctx*) ; 
 struct regmap* __devm_regmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sunxi_rsb_ctx*,struct regmap_config const*,struct lock_class_key*,char const*) ; 
 int /*<<< orphan*/  regmap_sunxi_rsb ; 
 struct sunxi_rsb_ctx* regmap_sunxi_rsb_init_ctx (struct sunxi_rsb_device*,struct regmap_config const*) ; 

struct regmap *__devm_regmap_init_sunxi_rsb(struct sunxi_rsb_device *rdev,
					    const struct regmap_config *config,
					    struct lock_class_key *lock_key,
					    const char *lock_name)
{
	struct sunxi_rsb_ctx *ctx = regmap_sunxi_rsb_init_ctx(rdev, config);

	if (IS_ERR(ctx))
		return ERR_CAST(ctx);

	return __devm_regmap_init(&rdev->dev, &regmap_sunxi_rsb, ctx, config,
				  lock_key, lock_name);
}