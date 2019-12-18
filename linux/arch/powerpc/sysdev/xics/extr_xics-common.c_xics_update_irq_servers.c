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
typedef  int u32 ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  boot_cpuid ; 
 int get_hard_smp_processor_id (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_cpu_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_devel (char*,int) ; 
 int xics_default_distrib_server ; 
 int xics_default_server ; 

void xics_update_irq_servers(void)
{
	int i, j;
	struct device_node *np;
	u32 ilen;
	const __be32 *ireg;
	u32 hcpuid;

	/* Find the server numbers for the boot cpu. */
	np = of_get_cpu_node(boot_cpuid, NULL);
	BUG_ON(!np);

	hcpuid = get_hard_smp_processor_id(boot_cpuid);
	xics_default_server = xics_default_distrib_server = hcpuid;

	pr_devel("xics: xics_default_server = 0x%x\n", xics_default_server);

	ireg = of_get_property(np, "ibm,ppc-interrupt-gserver#s", &ilen);
	if (!ireg) {
		of_node_put(np);
		return;
	}

	i = ilen / sizeof(int);

	/* Global interrupt distribution server is specified in the last
	 * entry of "ibm,ppc-interrupt-gserver#s" property. Get the last
	 * entry fom this property for current boot cpu id and use it as
	 * default distribution server
	 */
	for (j = 0; j < i; j += 2) {
		if (be32_to_cpu(ireg[j]) == hcpuid) {
			xics_default_distrib_server = be32_to_cpu(ireg[j+1]);
			break;
		}
	}
	pr_devel("xics: xics_default_distrib_server = 0x%x\n",
		 xics_default_distrib_server);
	of_node_put(np);
}