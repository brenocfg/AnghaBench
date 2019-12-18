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
struct TYPE_2__ {int /*<<< orphan*/  i; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct adm6996_priv {int /*<<< orphan*/  enable_vlan; } ;

/* Variables and functions */
 struct adm6996_priv* to_adm (struct switch_dev*) ; 

__attribute__((used)) static int
adm6996_get_enable_vlan(struct switch_dev *dev, const struct switch_attr *attr,
			struct switch_val *val)
{
	struct adm6996_priv *priv = to_adm(dev);

	val->value.i = priv->enable_vlan;

	return 0;
}