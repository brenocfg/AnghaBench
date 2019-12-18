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
struct gpio_desc {int dummy; } ;
struct ecx_plat_data {scalar_t__ post_clocks; scalar_t__ pre_clocks; int /*<<< orphan*/  n_ports; int /*<<< orphan*/  port_to_sgpio; struct gpio_desc** sgpio_gpiod; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct ata_port_info {int flags; } ;
struct ahci_host_priv {int em_buf_sz; int /*<<< orphan*/  em_msg_type; scalar_t__ em_loc; struct ecx_plat_data* plat_data; } ;

/* Variables and functions */
 int ATA_FLAG_EM ; 
 int ATA_FLAG_SW_ACTIVITY ; 
 int /*<<< orphan*/  EM_MSG_TYPE_LED ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int SGPIO_PINS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct gpio_desc* devm_gpiod_get_index (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_consumer_name (struct gpio_desc*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void highbank_set_em_messages(struct device *dev,
					struct ahci_host_priv *hpriv,
					struct ata_port_info *pi)
{
	struct device_node *np = dev->of_node;
	struct ecx_plat_data *pdata = hpriv->plat_data;
	int i;

	for (i = 0; i < SGPIO_PINS; i++) {
		struct gpio_desc *gpiod;

		gpiod = devm_gpiod_get_index(dev, "calxeda,sgpio", i,
					     GPIOD_OUT_HIGH);
		if (IS_ERR(gpiod)) {
			dev_err(dev, "failed to get GPIO %d\n", i);
			continue;
		}
		gpiod_set_consumer_name(gpiod, "CX SGPIO");

		pdata->sgpio_gpiod[i] = gpiod;
	}
	of_property_read_u32_array(np, "calxeda,led-order",
						pdata->port_to_sgpio,
						pdata->n_ports);
	if (of_property_read_u32(np, "calxeda,pre-clocks", &pdata->pre_clocks))
		pdata->pre_clocks = 0;
	if (of_property_read_u32(np, "calxeda,post-clocks",
				&pdata->post_clocks))
		pdata->post_clocks = 0;

	/* store em_loc */
	hpriv->em_loc = 0;
	hpriv->em_buf_sz = 4;
	hpriv->em_msg_type = EM_MSG_TYPE_LED;
	pi->flags |= ATA_FLAG_EM | ATA_FLAG_SW_ACTIVITY;
}