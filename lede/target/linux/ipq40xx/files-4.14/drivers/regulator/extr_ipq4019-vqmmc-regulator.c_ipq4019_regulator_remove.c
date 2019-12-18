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
struct regulator_dev {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct regulator_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_unregister (struct regulator_dev*) ; 

__attribute__((used)) static int ipq4019_regulator_remove(struct platform_device *pdev)
{
	struct regulator_dev *rdev = platform_get_drvdata(pdev);

	regulator_unregister(rdev);

	return 0;
}