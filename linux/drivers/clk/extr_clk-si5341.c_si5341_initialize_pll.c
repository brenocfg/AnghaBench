#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device_node {int dummy; } ;
struct clk_si5341 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  pxtal; TYPE_1__* i2c_client; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI5341_PLL_M_NUM ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int si5341_encode_44_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int si5341_initialize_pll(struct clk_si5341 *data)
{
	struct device_node *np = data->i2c_client->dev.of_node;
	u32 m_num = 0;
	u32 m_den = 0;

	if (of_property_read_u32(np, "silabs,pll-m-num", &m_num)) {
		dev_err(&data->i2c_client->dev,
			"PLL configuration requires silabs,pll-m-num\n");
	}
	if (of_property_read_u32(np, "silabs,pll-m-den", &m_den)) {
		dev_err(&data->i2c_client->dev,
			"PLL configuration requires silabs,pll-m-den\n");
	}

	if (!m_num || !m_den) {
		dev_err(&data->i2c_client->dev,
			"PLL configuration invalid, assume 14GHz\n");
		m_den = clk_get_rate(data->pxtal) / 10;
		m_num = 1400000000;
	}

	return si5341_encode_44_32(data->regmap,
			SI5341_PLL_M_NUM, m_num, m_den);
}