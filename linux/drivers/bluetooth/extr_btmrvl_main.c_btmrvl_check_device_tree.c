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
typedef  int u8 ;
typedef  int u16 ;
struct device_node {int dummy; } ;
struct btmrvl_sdio_card {struct device_node* plt_of_node; } ;
struct TYPE_2__ {int gpio_gap; struct btmrvl_sdio_card* card; } ;
struct btmrvl_private {TYPE_1__ btmrvl_dev; } ;

/* Variables and functions */
 int BT_CAL_DATA_SIZE ; 
 int BT_CAL_HDR_LEN ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int btmrvl_download_cal_data (struct btmrvl_private*,int*,int) ; 
 int of_property_read_u16 (struct device_node*,char*,int*) ; 
 int of_property_read_u8_array (struct device_node*,char*,int*,int) ; 

__attribute__((used)) static int btmrvl_check_device_tree(struct btmrvl_private *priv)
{
	struct device_node *dt_node;
	struct btmrvl_sdio_card *card = priv->btmrvl_dev.card;
	u8 cal_data[BT_CAL_HDR_LEN + BT_CAL_DATA_SIZE];
	int ret = 0;
	u16 gpio, gap;

	if (card->plt_of_node) {
		dt_node = card->plt_of_node;
		ret = of_property_read_u16(dt_node, "marvell,wakeup-pin",
					   &gpio);
		if (ret)
			gpio = (priv->btmrvl_dev.gpio_gap & 0xff00) >> 8;

		ret = of_property_read_u16(dt_node, "marvell,wakeup-gap-ms",
					   &gap);
		if (ret)
			gap = (u8)(priv->btmrvl_dev.gpio_gap & 0x00ff);

		priv->btmrvl_dev.gpio_gap = (gpio << 8) + gap;

		ret = of_property_read_u8_array(dt_node, "marvell,cal-data",
						cal_data + BT_CAL_HDR_LEN,
						BT_CAL_DATA_SIZE);
		if (ret)
			return ret;

		BT_DBG("Use cal data from device tree");
		ret = btmrvl_download_cal_data(priv, cal_data,
					       BT_CAL_DATA_SIZE);
		if (ret)
			BT_ERR("Fail to download calibrate data");
	}

	return ret;
}