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
struct switch_val {size_t port_vlan; TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct psb6970_priv {int /*<<< orphan*/ * vlan_id; } ;

/* Variables and functions */
 struct psb6970_priv* to_psb6970 (struct switch_dev*) ; 

__attribute__((used)) static int
psb6970_set_vid(struct switch_dev *dev, const struct switch_attr *attr,
		struct switch_val *val)
{
	struct psb6970_priv *priv = to_psb6970(dev);
	priv->vlan_id[val->port_vlan] = val->value.i;
	return 0;
}