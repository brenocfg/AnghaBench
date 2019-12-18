#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk_cdce925_output {int index; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int CDCE925_REG_Y1SPIPDIVH ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void cdce925_clk_activate(struct clk_cdce925_output *data)
{
	switch (data->index) {
	case 0:
		regmap_update_bits(data->chip->regmap,
			CDCE925_REG_Y1SPIPDIVH, 0x0c, 0x0c);
		break;
	case 1:
	case 2:
		regmap_update_bits(data->chip->regmap, 0x14, 0x03, 0x03);
		break;
	case 3:
	case 4:
		regmap_update_bits(data->chip->regmap, 0x24, 0x03, 0x03);
		break;
	case 5:
	case 6:
		regmap_update_bits(data->chip->regmap, 0x34, 0x03, 0x03);
		break;
	case 7:
	case 8:
		regmap_update_bits(data->chip->regmap, 0x44, 0x03, 0x03);
		break;
	}
}