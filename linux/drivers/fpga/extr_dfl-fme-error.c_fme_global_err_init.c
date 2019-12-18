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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dfl_feature {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fme_err_mask (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fme_global_err_init(struct platform_device *pdev,
			       struct dfl_feature *feature)
{
	fme_err_mask(&pdev->dev, false);

	return 0;
}