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
struct TYPE_3__ {int /*<<< orphan*/  i; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct ar8xxx_priv {int /*<<< orphan*/  reg_mutex; TYPE_2__* chip; int /*<<< orphan*/  source_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_mirror_regs ) (struct ar8xxx_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ar8xxx_priv*) ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

int
ar8xxx_sw_set_mirror_source_port(struct switch_dev *dev,
				 const struct switch_attr *attr,
				 struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	mutex_lock(&priv->reg_mutex);
	priv->source_port = val->value.i;
	priv->chip->set_mirror_regs(priv);
	mutex_unlock(&priv->reg_mutex);

	return 0;
}