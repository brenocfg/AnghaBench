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
typedef  int u32 ;
struct TYPE_2__ {int i; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct ar8xxx_priv {int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 int AR8327_FRAME_ACK_CTRL_IGMP_V3_EN ; 
 int /*<<< orphan*/  AR8327_REG_FRAME_ACK_CTRL1 ; 
 int ar8xxx_read (struct ar8xxx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

int
ar8327_sw_get_igmp_v3(struct switch_dev *dev,
		      const struct switch_attr *attr,
		      struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	u32 val_reg;

	mutex_lock(&priv->reg_mutex);
	val_reg = ar8xxx_read(priv, AR8327_REG_FRAME_ACK_CTRL1);
	val->value.i = ((val_reg & AR8327_FRAME_ACK_CTRL_IGMP_V3_EN) != 0);
	mutex_unlock(&priv->reg_mutex);

	return 0;
}