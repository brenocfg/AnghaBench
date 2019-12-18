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
struct seq_file {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MODULE_NAME ; 
 int /*<<< orphan*/  MODULE_VERS ; 
 unsigned int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 void* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int pseries_lparcfg_data (struct seq_file*,void*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int lparcfg_data(struct seq_file *m, void *v)
{
	struct device_node *rootdn;
	const char *model = "";
	const char *system_id = "";
	const char *tmp;
	const __be32 *lp_index_ptr;
	unsigned int lp_index = 0;

	seq_printf(m, "%s %s\n", MODULE_NAME, MODULE_VERS);

	rootdn = of_find_node_by_path("/");
	if (rootdn) {
		tmp = of_get_property(rootdn, "model", NULL);
		if (tmp)
			model = tmp;
		tmp = of_get_property(rootdn, "system-id", NULL);
		if (tmp)
			system_id = tmp;
		lp_index_ptr = of_get_property(rootdn, "ibm,partition-no",
					NULL);
		if (lp_index_ptr)
			lp_index = be32_to_cpup(lp_index_ptr);
		of_node_put(rootdn);
	}
	seq_printf(m, "serial_number=%s\n", system_id);
	seq_printf(m, "system_type=%s\n", model);
	seq_printf(m, "partition_id=%d\n", (int)lp_index);

	return pseries_lparcfg_data(m, v);
}