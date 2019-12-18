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
struct vio_dev {char* type; } ;
struct device_node {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 

__attribute__((used)) static ssize_t modalias_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	const struct vio_dev *vio_dev = to_vio_dev(dev);
	struct device_node *dn;
	const char *cp;

	dn = dev->of_node;
	if (!dn) {
		strcpy(buf, "\n");
		return strlen(buf);
	}
	cp = of_get_property(dn, "compatible", NULL);
	if (!cp) {
		strcpy(buf, "\n");
		return strlen(buf);
	}

	return sprintf(buf, "vio:T%sS%s\n", vio_dev->type, cp);
}