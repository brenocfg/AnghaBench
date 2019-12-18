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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct platform_device* ERR_PTR (int) ; 
 int NUMA_NO_NODE ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  set_dev_node (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct platform_device *
test_platform_device_register_node(char *name, int id, int nid)
{
	struct platform_device *pdev;
	int ret;

	pdev = platform_device_alloc(name, id);
	if (!pdev)
		return NULL;

	if (nid != NUMA_NO_NODE)
		set_dev_node(&pdev->dev, nid);

	ret = platform_device_add(pdev);
	if (ret) {
		platform_device_put(pdev);
		return ERR_PTR(ret);
	}

	return pdev;

}