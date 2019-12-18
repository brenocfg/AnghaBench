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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hd44780 {void** pins; } ;
struct charlcd {int height; int width; int bwidth; int ifwidth; int /*<<< orphan*/ * ops; struct hd44780* drvdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 size_t PIN_CTRL_BL ; 
 size_t PIN_CTRL_E ; 
 size_t PIN_CTRL_RS ; 
 size_t PIN_CTRL_RW ; 
 unsigned int PIN_DATA0 ; 
 unsigned int PIN_DATA4 ; 
 int PTR_ERR (void*) ; 
 struct charlcd* charlcd_alloc (int) ; 
 int /*<<< orphan*/  charlcd_free (struct charlcd*) ; 
 int charlcd_register (struct charlcd*) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_index (struct device*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 int gpiod_count (struct device*,char*) ; 
 int /*<<< orphan*/  hd44780_ops_gpio4 ; 
 int /*<<< orphan*/  hd44780_ops_gpio8 ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct charlcd*) ; 

__attribute__((used)) static int hd44780_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	unsigned int i, base;
	struct charlcd *lcd;
	struct hd44780 *hd;
	int ifwidth, ret;

	/* Required pins */
	ifwidth = gpiod_count(dev, "data");
	if (ifwidth < 0)
		return ifwidth;

	switch (ifwidth) {
	case 4:
		base = PIN_DATA4;
		break;
	case 8:
		base = PIN_DATA0;
		break;
	default:
		return -EINVAL;
	}

	lcd = charlcd_alloc(sizeof(struct hd44780));
	if (!lcd)
		return -ENOMEM;

	hd = lcd->drvdata;

	for (i = 0; i < ifwidth; i++) {
		hd->pins[base + i] = devm_gpiod_get_index(dev, "data", i,
							  GPIOD_OUT_LOW);
		if (IS_ERR(hd->pins[base + i])) {
			ret = PTR_ERR(hd->pins[base + i]);
			goto fail;
		}
	}

	hd->pins[PIN_CTRL_E] = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(hd->pins[PIN_CTRL_E])) {
		ret = PTR_ERR(hd->pins[PIN_CTRL_E]);
		goto fail;
	}

	hd->pins[PIN_CTRL_RS] = devm_gpiod_get(dev, "rs", GPIOD_OUT_HIGH);
	if (IS_ERR(hd->pins[PIN_CTRL_RS])) {
		ret = PTR_ERR(hd->pins[PIN_CTRL_RS]);
		goto fail;
	}

	/* Optional pins */
	hd->pins[PIN_CTRL_RW] = devm_gpiod_get_optional(dev, "rw",
							GPIOD_OUT_LOW);
	if (IS_ERR(hd->pins[PIN_CTRL_RW])) {
		ret = PTR_ERR(hd->pins[PIN_CTRL_RW]);
		goto fail;
	}

	hd->pins[PIN_CTRL_BL] = devm_gpiod_get_optional(dev, "backlight",
							GPIOD_OUT_LOW);
	if (IS_ERR(hd->pins[PIN_CTRL_BL])) {
		ret = PTR_ERR(hd->pins[PIN_CTRL_BL]);
		goto fail;
	}

	/* Required properties */
	ret = device_property_read_u32(dev, "display-height-chars",
				       &lcd->height);
	if (ret)
		goto fail;
	ret = device_property_read_u32(dev, "display-width-chars", &lcd->width);
	if (ret)
		goto fail;

	/*
	 * On displays with more than two rows, the internal buffer width is
	 * usually equal to the display width
	 */
	if (lcd->height > 2)
		lcd->bwidth = lcd->width;

	/* Optional properties */
	device_property_read_u32(dev, "internal-buffer-width", &lcd->bwidth);

	lcd->ifwidth = ifwidth;
	lcd->ops = ifwidth == 8 ? &hd44780_ops_gpio8 : &hd44780_ops_gpio4;

	ret = charlcd_register(lcd);
	if (ret)
		goto fail;

	platform_set_drvdata(pdev, lcd);
	return 0;

fail:
	charlcd_free(lcd);
	return ret;
}