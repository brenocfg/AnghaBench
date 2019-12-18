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
struct platform_device {int dummy; } ;
struct mcs814x_rng_priv {scalar_t__ priv; } ;
struct hwrng {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwrng_unregister (struct mcs814x_rng_priv*) ; 
 int /*<<< orphan*/  kfree (struct mcs814x_rng_priv*) ; 
 struct mcs814x_rng_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcs814x_rng_remove(struct platform_device *pdev)
{
	struct hwrng *rng = platform_get_drvdata(pdev);
	struct mcs814x_rng_priv *priv = (struct mcs814x_rng_priv *)rng->priv;

	hwrng_unregister(rng);
	kfree(priv);
	kfree(rng);
	platform_set_drvdata(pdev, NULL);

	return 0;
}