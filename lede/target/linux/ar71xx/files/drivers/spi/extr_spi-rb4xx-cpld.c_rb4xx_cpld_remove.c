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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct rb4xx_cpld {int dummy; } ;

/* Variables and functions */
 struct rb4xx_cpld* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rb4xx_cpld*) ; 
 int /*<<< orphan*/ * rb4xx_cpld ; 

__attribute__((used)) static int rb4xx_cpld_remove(struct spi_device *spi)
{
	struct rb4xx_cpld *cpld;

	rb4xx_cpld = NULL;
	cpld = dev_get_drvdata(&spi->dev);
	dev_set_drvdata(&spi->dev, NULL);
	kfree(cpld);

	return 0;
}