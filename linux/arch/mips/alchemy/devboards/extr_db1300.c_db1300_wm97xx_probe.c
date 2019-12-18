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
struct wm97xx {int /*<<< orphan*/  pen_irq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB1300_AC97_PEN_INT ; 
 int /*<<< orphan*/  WM97XX_GPIO_13 ; 
 int /*<<< orphan*/  WM97XX_GPIO_3 ; 
 int /*<<< orphan*/  WM97XX_GPIO_IN ; 
 int /*<<< orphan*/  WM97XX_GPIO_NOTSTICKY ; 
 int /*<<< orphan*/  WM97XX_GPIO_NOWAKE ; 
 int /*<<< orphan*/  WM97XX_GPIO_OUT ; 
 int /*<<< orphan*/  WM97XX_GPIO_POL_LOW ; 
 int /*<<< orphan*/  WM97XX_GPIO_STICKY ; 
 int /*<<< orphan*/  WM97XX_GPIO_WAKE ; 
 int /*<<< orphan*/  db1300_wm97xx_ops ; 
 struct wm97xx* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wm97xx_config_gpio (struct wm97xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm97xx_register_mach_ops (struct wm97xx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int db1300_wm97xx_probe(struct platform_device *pdev)
{
	struct wm97xx *wm = platform_get_drvdata(pdev);

	/* external pendown indicator */
	wm97xx_config_gpio(wm, WM97XX_GPIO_13, WM97XX_GPIO_IN,
			   WM97XX_GPIO_POL_LOW, WM97XX_GPIO_STICKY,
			   WM97XX_GPIO_WAKE);

	/* internal "virtual" pendown gpio */
	wm97xx_config_gpio(wm, WM97XX_GPIO_3, WM97XX_GPIO_OUT,
			   WM97XX_GPIO_POL_LOW, WM97XX_GPIO_NOTSTICKY,
			   WM97XX_GPIO_NOWAKE);

	wm->pen_irq = DB1300_AC97_PEN_INT;

	return wm97xx_register_mach_ops(wm, &db1300_wm97xx_ops);
}