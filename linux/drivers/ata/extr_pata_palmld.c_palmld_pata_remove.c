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
struct palmld_pata {int /*<<< orphan*/  power; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_platform_remove_one (struct platform_device*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct palmld_pata* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int palmld_pata_remove(struct platform_device *pdev)
{
	struct palmld_pata *lda = platform_get_drvdata(pdev);

	ata_platform_remove_one(pdev);

	/* power down the HDD */
	gpiod_set_value(lda->power, 0);

	return 0;
}