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
typedef  int /*<<< orphan*/  u32 ;
struct property {int length; struct dynamic_dma_window_prop* value; } ;
struct dynamic_dma_window_prop {int /*<<< orphan*/  window_shift; int /*<<< orphan*/  liobn; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECT64_PROPNAME ; 
 unsigned long long PAGE_SHIFT ; 
 unsigned long long be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct property* of_find_property (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ *,int) ; 
 int of_remove_property (struct device_node*,struct property*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct device_node*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,struct device_node*,...) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int tce_clearrange_multi_pSeriesLP (int /*<<< orphan*/ ,unsigned long long,struct dynamic_dma_window_prop*) ; 

__attribute__((used)) static void remove_ddw(struct device_node *np, bool remove_prop)
{
	struct dynamic_dma_window_prop *dwp;
	struct property *win64;
	u32 ddw_avail[3];
	u64 liobn;
	int ret = 0;

	ret = of_property_read_u32_array(np, "ibm,ddw-applicable",
					 &ddw_avail[0], 3);

	win64 = of_find_property(np, DIRECT64_PROPNAME, NULL);
	if (!win64)
		return;

	if (ret || win64->length < sizeof(*dwp))
		goto delprop;

	dwp = win64->value;
	liobn = (u64)be32_to_cpu(dwp->liobn);

	/* clear the whole window, note the arg is in kernel pages */
	ret = tce_clearrange_multi_pSeriesLP(0,
		1ULL << (be32_to_cpu(dwp->window_shift) - PAGE_SHIFT), dwp);
	if (ret)
		pr_warn("%pOF failed to clear tces in window.\n",
			np);
	else
		pr_debug("%pOF successfully cleared tces in window.\n",
			 np);

	ret = rtas_call(ddw_avail[2], 1, 1, NULL, liobn);
	if (ret)
		pr_warn("%pOF: failed to remove direct window: rtas returned "
			"%d to ibm,remove-pe-dma-window(%x) %llx\n",
			np, ret, ddw_avail[2], liobn);
	else
		pr_debug("%pOF: successfully removed direct window: rtas returned "
			"%d to ibm,remove-pe-dma-window(%x) %llx\n",
			np, ret, ddw_avail[2], liobn);

delprop:
	if (remove_prop)
		ret = of_remove_property(np, win64);
	if (ret)
		pr_warn("%pOF: failed to remove direct window property: %d\n",
			np, ret);
}