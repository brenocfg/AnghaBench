#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct serdev_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct btmtkuart_dev {int desired_speed; void* clk; void* reset; void* pins_runtime; void* pinctrl; void* pins_boot; void* boot; void* osc; void* vcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ btmtkuart_is_builtin_soc (struct btmtkuart_dev*) ; 
 scalar_t__ btmtkuart_is_standalone (struct btmtkuart_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 void* devm_clk_get_optional (TYPE_1__*,char*) ; 
 void* devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 void* devm_pinctrl_get (TYPE_1__*) ; 
 void* devm_regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 void* pinctrl_lookup_state (void*,char*) ; 
 struct btmtkuart_dev* serdev_device_get_drvdata (struct serdev_device*) ; 

__attribute__((used)) static int btmtkuart_parse_dt(struct serdev_device *serdev)
{
	struct btmtkuart_dev *bdev = serdev_device_get_drvdata(serdev);
	struct device_node *node = serdev->dev.of_node;
	u32 speed = 921600;
	int err;

	if (btmtkuart_is_standalone(bdev)) {
		of_property_read_u32(node, "current-speed", &speed);

		bdev->desired_speed = speed;

		bdev->vcc = devm_regulator_get(&serdev->dev, "vcc");
		if (IS_ERR(bdev->vcc)) {
			err = PTR_ERR(bdev->vcc);
			return err;
		}

		bdev->osc = devm_clk_get_optional(&serdev->dev, "osc");
		if (IS_ERR(bdev->osc)) {
			err = PTR_ERR(bdev->osc);
			return err;
		}

		bdev->boot = devm_gpiod_get_optional(&serdev->dev, "boot",
						     GPIOD_OUT_LOW);
		if (IS_ERR(bdev->boot)) {
			err = PTR_ERR(bdev->boot);
			return err;
		}

		bdev->pinctrl = devm_pinctrl_get(&serdev->dev);
		if (IS_ERR(bdev->pinctrl)) {
			err = PTR_ERR(bdev->pinctrl);
			return err;
		}

		bdev->pins_boot = pinctrl_lookup_state(bdev->pinctrl,
						       "default");
		if (IS_ERR(bdev->pins_boot) && !bdev->boot) {
			err = PTR_ERR(bdev->pins_boot);
			dev_err(&serdev->dev,
				"Should assign RXD to LOW at boot stage\n");
			return err;
		}

		bdev->pins_runtime = pinctrl_lookup_state(bdev->pinctrl,
							  "runtime");
		if (IS_ERR(bdev->pins_runtime)) {
			err = PTR_ERR(bdev->pins_runtime);
			return err;
		}

		bdev->reset = devm_gpiod_get_optional(&serdev->dev, "reset",
						      GPIOD_OUT_LOW);
		if (IS_ERR(bdev->reset)) {
			err = PTR_ERR(bdev->reset);
			return err;
		}
	} else if (btmtkuart_is_builtin_soc(bdev)) {
		bdev->clk = devm_clk_get(&serdev->dev, "ref");
		if (IS_ERR(bdev->clk))
			return PTR_ERR(bdev->clk);
	}

	return 0;
}