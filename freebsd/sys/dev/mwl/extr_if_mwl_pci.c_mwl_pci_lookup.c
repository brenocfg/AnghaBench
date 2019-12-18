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
struct mwl_pci_ident {int vendor; int device; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct mwl_pci_ident* mwl_pci_ids ; 

__attribute__((used)) const static struct mwl_pci_ident *
mwl_pci_lookup(int vendor, int device)
{
	const struct mwl_pci_ident *ident;

	for (ident = mwl_pci_ids; ident->name != NULL; ident++)
		if (vendor == ident->vendor && device == ident->device)
			return ident;
	return NULL;
}