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
typedef  scalar_t__ u64 ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,unsigned long long,char const*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_translate_address (struct device_node*,int /*<<< orphan*/  const*) ; 

char *ap_cp_unique_name(struct device *dev, struct device_node *np,
			const char *name)
{
	const __be32 *reg;
	u64 addr;

	/* Do not create a name if there is no clock */
	if (!name)
		return NULL;

	reg = of_get_property(np, "reg", NULL);
	addr = of_translate_address(np, reg);
	return devm_kasprintf(dev, GFP_KERNEL, "%llx-%s",
			      (unsigned long long)addr, name);
}