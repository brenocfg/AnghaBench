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
struct clp_req_rsp_list_pci {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __clp_add ; 
 struct clp_req_rsp_list_pci* clp_alloc_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clp_free_block (struct clp_req_rsp_list_pci*) ; 
 int clp_list_pci (struct clp_req_rsp_list_pci*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int clp_scan_pci_devices(void)
{
	struct clp_req_rsp_list_pci *rrb;
	int rc;

	rrb = clp_alloc_block(GFP_KERNEL);
	if (!rrb)
		return -ENOMEM;

	rc = clp_list_pci(rrb, NULL, __clp_add);

	clp_free_block(rrb);
	return rc;
}