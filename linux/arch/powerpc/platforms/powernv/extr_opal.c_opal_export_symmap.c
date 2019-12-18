#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/  const) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,unsigned int*) ; 
 int /*<<< orphan*/  opal_kobj ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 TYPE_1__ symbol_map_attr ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void opal_export_symmap(void)
{
	const __be64 *syms;
	unsigned int size;
	struct device_node *fw;
	int rc;

	fw = of_find_node_by_path("/ibm,opal/firmware");
	if (!fw)
		return;
	syms = of_get_property(fw, "symbol-map", &size);
	if (!syms || size != 2 * sizeof(__be64))
		return;

	/* Setup attributes */
	symbol_map_attr.private = __va(be64_to_cpu(syms[0]));
	symbol_map_attr.size = be64_to_cpu(syms[1]);

	rc = sysfs_create_bin_file(opal_kobj, &symbol_map_attr);
	if (rc)
		pr_warn("Error %d creating OPAL symbols file\n", rc);
}