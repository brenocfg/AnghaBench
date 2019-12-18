#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {TYPE_1__* its; } ;
struct iort_node {scalar_t__ type; TYPE_2__ entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  xref; } ;

/* Variables and functions */
 scalar_t__ ACPI_IORT_NODE_ITS_GROUP ; 
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct iort_node* iort_pci_rc_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

int
acpi_iort_map_pci_msi(u_int seg, u_int rid, u_int *xref, u_int *devid)
{
	struct iort_node *node;

	node = iort_pci_rc_map(seg, rid, ACPI_IORT_NODE_ITS_GROUP, devid);
	if (node == NULL)
		return (ENOENT);

	/* This should be an ITS node */
	KASSERT(node->type == ACPI_IORT_NODE_ITS_GROUP, ("bad group"));

	/* return first node, we don't handle more than that now. */
	*xref = node->entries.its[0].xref;
	return (0);
}