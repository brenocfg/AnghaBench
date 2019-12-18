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
struct timeriomem_rng_private {int /*<<< orphan*/  timer; int /*<<< orphan*/  rng_ops; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 struct timeriomem_rng_private* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int timeriomem_rng_remove(struct platform_device *pdev)
{
	struct timeriomem_rng_private *priv = platform_get_drvdata(pdev);

	hwrng_unregister(&priv->rng_ops);
	hrtimer_cancel(&priv->timer);

	return 0;
}