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
struct ipoib_dev_priv {TYPE_1__* parent; } ;
struct ifnet {struct ipoib_dev_priv* if_softc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct ifnet* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t show_parent(struct device *d, struct device_attribute *attr,
			   char *buf)
{
	struct ifnet *dev = to_net_dev(d);
	struct ipoib_dev_priv *priv = dev->if_softc;

	return sprintf(buf, "%s\n", priv->parent->name);
}