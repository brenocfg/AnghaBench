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

/* Variables and functions */
 int DBCR0_RST_SYSTEM ; 
 int /*<<< orphan*/  SPRN_DBCR0 ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 struct device_node* of_get_cpu_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

void ppc4xx_reset_system(char *cmd)
{
	struct device_node *np;
	u32 reset_type = DBCR0_RST_SYSTEM;
	const u32 *prop;

	np = of_get_cpu_node(0, NULL);
	if (np) {
		prop = of_get_property(np, "reset-type", NULL);

		/*
		 * Check if property exists and if it is in range:
		 * 1 - PPC4xx core reset
		 * 2 - PPC4xx chip reset
		 * 3 - PPC4xx system reset (default)
		 */
		if ((prop) && ((prop[0] >= 1) && (prop[0] <= 3)))
			reset_type = prop[0] << 28;
	}

	mtspr(SPRN_DBCR0, mfspr(SPRN_DBCR0) | reset_type);

	while (1)
		;	/* Just in case the reset doesn't work */
}