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
struct resource {int /*<<< orphan*/  start; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_reset_base ; 
 int /*<<< orphan*/  cpu_reset_size ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_address_to_resource (struct device_node*,int,struct resource*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int mvebu_cpu_reset_map(struct device_node *np, int res_idx)
{
	struct resource res;

	if (of_address_to_resource(np, res_idx, &res)) {
		pr_err("unable to get resource\n");
		return -ENOENT;
	}

	if (!request_mem_region(res.start, resource_size(&res),
				np->full_name)) {
		pr_err("unable to request region\n");
		return -EBUSY;
	}

	cpu_reset_base = ioremap(res.start, resource_size(&res));
	if (!cpu_reset_base) {
		pr_err("unable to map registers\n");
		release_mem_region(res.start, resource_size(&res));
		return -ENOMEM;
	}

	cpu_reset_size = resource_size(&res);

	return 0;
}