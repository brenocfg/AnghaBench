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
struct sysc {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysc_check_quirk_stdout (struct sysc*,struct device_node*) ; 
 int /*<<< orphan*/  sysc_parse_dts_quirks (struct sysc*,struct device_node*,int) ; 

__attribute__((used)) static void sysc_check_one_child(struct sysc *ddata,
				 struct device_node *np)
{
	const char *name;

	name = of_get_property(np, "ti,hwmods", NULL);
	if (name)
		dev_warn(ddata->dev, "really a child ti,hwmods property?");

	sysc_check_quirk_stdout(ddata, np);
	sysc_parse_dts_quirks(ddata, np, true);
}