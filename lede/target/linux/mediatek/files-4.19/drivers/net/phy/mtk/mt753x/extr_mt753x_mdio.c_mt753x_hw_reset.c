#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct reset_control {int dummy; } ;
struct gsw_mt753x {int reset_pin; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int IS_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 int devm_gpio_request (TYPE_1__*,int,char*) ; 
 struct reset_control* devm_reset_control_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 

__attribute__((used)) static int mt753x_hw_reset(struct gsw_mt753x *gsw)
{
	struct device_node *np = gsw->dev->of_node;
	struct reset_control *rstc;
	int mcm;
	int ret = -EINVAL;

	mcm = of_property_read_bool(np, "mediatek,mcm");
	if (mcm) {
		rstc = devm_reset_control_get(gsw->dev, "mcm");
		ret = IS_ERR(rstc);
		if (IS_ERR(rstc)) {
			dev_err(gsw->dev, "Missing reset ctrl of switch\n");
			return ret;
		}

		reset_control_assert(rstc);
		msleep(30);
		reset_control_deassert(rstc);

		gsw->reset_pin = -1;
		return 0;
	}

	gsw->reset_pin = of_get_named_gpio(np, "reset-gpios", 0);
	if (gsw->reset_pin < 0) {
		dev_err(gsw->dev, "Missing reset pin of switch\n");
		return ret;
	}

	ret = devm_gpio_request(gsw->dev, gsw->reset_pin, "mt753x-reset");
	if (ret) {
		dev_info(gsw->dev, "Failed to request gpio %d\n",
			 gsw->reset_pin);
		return ret;
	}

	gpio_direction_output(gsw->reset_pin, 0);
	msleep(30);
	gpio_set_value(gsw->reset_pin, 1);
	msleep(500);

	return 0;
}