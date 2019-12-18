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
struct ar8xxx_priv {struct ar8327_data* chip_data; } ;
struct ar8327_led {int /*<<< orphan*/  pattern; int /*<<< orphan*/  led_num; scalar_t__ enable_hw_mode; } ;
struct ar8327_data {unsigned int num_leds; struct ar8327_led** leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8327_LED_PATTERN_OFF ; 
 int /*<<< orphan*/  AR8327_LED_PATTERN_RULE ; 
 int /*<<< orphan*/  CONFIG_AR8216_PHY_LEDS ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8327_set_led_pattern (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar8327_leds_init(struct ar8xxx_priv *priv)
{
	struct ar8327_data *data = priv->chip_data;
	unsigned i;

	if (!IS_ENABLED(CONFIG_AR8216_PHY_LEDS))
		return;

	for (i = 0; i < data->num_leds; i++) {
		struct ar8327_led *aled;

		aled = data->leds[i];

		if (aled->enable_hw_mode)
			aled->pattern = AR8327_LED_PATTERN_RULE;
		else
			aled->pattern = AR8327_LED_PATTERN_OFF;

		ar8327_set_led_pattern(priv, aled->led_num, aled->pattern);
	}
}