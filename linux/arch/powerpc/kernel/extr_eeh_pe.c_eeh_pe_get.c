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
struct eeh_pe_get_flag {int member_0; int member_1; } ;
struct eeh_pe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __eeh_pe_get ; 
 struct eeh_pe* eeh_pe_traverse (struct eeh_pe*,int /*<<< orphan*/ ,struct eeh_pe_get_flag*) ; 
 struct eeh_pe* eeh_phb_pe_get (struct pci_controller*) ; 

struct eeh_pe *eeh_pe_get(struct pci_controller *phb,
		int pe_no, int config_addr)
{
	struct eeh_pe *root = eeh_phb_pe_get(phb);
	struct eeh_pe_get_flag tmp = { pe_no, config_addr };
	struct eeh_pe *pe;

	pe = eeh_pe_traverse(root, __eeh_pe_get, &tmp);

	return pe;
}