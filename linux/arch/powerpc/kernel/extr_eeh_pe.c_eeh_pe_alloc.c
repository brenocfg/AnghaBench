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
struct pci_controller {int dummy; } ;
struct eeh_pe {int type; void* data; int /*<<< orphan*/  edevs; int /*<<< orphan*/  child_list; struct pci_controller* phb; } ;

/* Variables and functions */
 size_t ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_line_size () ; 
 scalar_t__ eeh_pe_aux_size ; 
 struct eeh_pe* kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct eeh_pe *eeh_pe_alloc(struct pci_controller *phb, int type)
{
	struct eeh_pe *pe;
	size_t alloc_size;

	alloc_size = sizeof(struct eeh_pe);
	if (eeh_pe_aux_size) {
		alloc_size = ALIGN(alloc_size, cache_line_size());
		alloc_size += eeh_pe_aux_size;
	}

	/* Allocate PHB PE */
	pe = kzalloc(alloc_size, GFP_KERNEL);
	if (!pe) return NULL;

	/* Initialize PHB PE */
	pe->type = type;
	pe->phb = phb;
	INIT_LIST_HEAD(&pe->child_list);
	INIT_LIST_HEAD(&pe->edevs);

	pe->data = (void *)pe + ALIGN(sizeof(struct eeh_pe),
				      cache_line_size());
	return pe;
}