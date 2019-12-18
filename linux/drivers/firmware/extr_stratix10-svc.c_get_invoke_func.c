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
typedef  int /*<<< orphan*/  svc_invoke_fn ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 scalar_t__ of_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * svc_smccc_hvc ; 
 int /*<<< orphan*/ * svc_smccc_smc ; 

__attribute__((used)) static svc_invoke_fn *get_invoke_func(struct device *dev)
{
	const char *method;

	if (of_property_read_string(dev->of_node, "method", &method)) {
		dev_warn(dev, "missing \"method\" property\n");
		return ERR_PTR(-ENXIO);
	}

	if (!strcmp(method, "smc"))
		return svc_smccc_smc;
	if (!strcmp(method, "hvc"))
		return svc_smccc_hvc;

	dev_warn(dev, "invalid \"method\" property: %s\n", method);

	return ERR_PTR(-EINVAL);
}