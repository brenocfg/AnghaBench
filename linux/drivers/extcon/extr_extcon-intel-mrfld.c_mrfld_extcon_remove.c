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
struct mrfld_extcon_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mrfld_extcon_sw_control (struct mrfld_extcon_data*,int) ; 
 struct mrfld_extcon_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mrfld_extcon_remove(struct platform_device *pdev)
{
	struct mrfld_extcon_data *data = platform_get_drvdata(pdev);

	mrfld_extcon_sw_control(data, false);

	return 0;
}