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
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
struct switch_val {TYPE_1__ value; int /*<<< orphan*/  len; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct b53_device {int enabled_ports; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_BUF_SIZE ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct b53_device* sw_to_b53 (struct switch_dev*) ; 

__attribute__((used)) static int b53_global_get_ports(struct switch_dev *dev,
				const struct switch_attr *attr,
				struct switch_val *val)
{
	struct b53_device *priv = sw_to_b53(dev);

	val->len = snprintf(priv->buf, B53_BUF_SIZE, "0x%04x",
			    priv->enabled_ports);
	val->value.s = priv->buf;

	return 0;
}