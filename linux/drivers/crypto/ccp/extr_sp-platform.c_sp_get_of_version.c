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
struct sp_dev_vdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp_of_match ; 

__attribute__((used)) static struct sp_dev_vdata *sp_get_of_version(struct platform_device *pdev)
{
#ifdef CONFIG_OF
	const struct of_device_id *match;

	match = of_match_node(sp_of_match, pdev->dev.of_node);
	if (match && match->data)
		return (struct sp_dev_vdata *)match->data;
#endif
	return NULL;
}