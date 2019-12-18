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
struct img_ascii_lcd_ctx {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_message ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct img_ascii_lcd_ctx* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int img_ascii_lcd_remove(struct platform_device *pdev)
{
	struct img_ascii_lcd_ctx *ctx = platform_get_drvdata(pdev);

	device_remove_file(&pdev->dev, &dev_attr_message);
	del_timer_sync(&ctx->timer);
	return 0;
}