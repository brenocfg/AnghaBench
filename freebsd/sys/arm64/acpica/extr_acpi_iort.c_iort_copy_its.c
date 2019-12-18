#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct iort_its_entry* its; } ;
struct iort_node {int nentries; TYPE_1__ entries; scalar_t__ usecount; } ;
struct iort_its_entry {int pxm; scalar_t__ xref; int /*<<< orphan*/  its_id; } ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_7__ {int ItsCount; int /*<<< orphan*/ * Identifiers; } ;
struct TYPE_6__ {scalar_t__ NodeData; } ;
typedef  TYPE_2__ ACPI_IORT_NODE ;
typedef  TYPE_3__ ACPI_IORT_ITS_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct iort_its_entry* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iort_copy_its(struct iort_node *node, ACPI_IORT_NODE *node_entry)
{
	struct iort_its_entry *its;
	ACPI_IORT_ITS_GROUP *itsg_entry;
	UINT32 *id;
	int i;

	itsg_entry = (ACPI_IORT_ITS_GROUP *)node_entry->NodeData;
	node->nentries = itsg_entry->ItsCount;
	node->usecount = 0;
	its = malloc(sizeof(*its) * node->nentries, M_DEVBUF, M_WAITOK | M_ZERO);
	node->entries.its = its;
	id = &itsg_entry->Identifiers[0];
	for (i = 0; i < node->nentries; i++, its++, id++) {
		its->its_id = *id;
		its->pxm = -1;
		its->xref = 0;
	}
}