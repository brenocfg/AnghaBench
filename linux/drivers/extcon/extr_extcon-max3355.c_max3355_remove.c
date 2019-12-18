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
struct max3355_data {int /*<<< orphan*/  shdn_gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max3355_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int max3355_remove(struct platform_device *pdev)
{
	struct max3355_data *data = platform_get_drvdata(pdev);

	gpiod_set_value_cansleep(data->shdn_gpiod, 0);

	return 0;
}