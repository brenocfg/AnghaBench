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
struct fpga_bridge {struct alt_fpga2sdram_data* priv; } ;
struct alt_fpga2sdram_data {int mask; int /*<<< orphan*/  sdrctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALT_SDR_CTL_FPGAPORTRST_OFST ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int alt_fpga2sdram_enable_show(struct fpga_bridge *bridge)
{
	struct alt_fpga2sdram_data *priv = bridge->priv;
	int value;

	regmap_read(priv->sdrctl, ALT_SDR_CTL_FPGAPORTRST_OFST, &value);

	return (value & priv->mask) == priv->mask;
}