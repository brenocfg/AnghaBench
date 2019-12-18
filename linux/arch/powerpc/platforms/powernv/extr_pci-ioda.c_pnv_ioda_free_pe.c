#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pe_alloc; } ;
struct pnv_phb {TYPE_1__ ioda; } ;
struct pnv_ioda_pe {unsigned int pe_number; int /*<<< orphan*/  npucomp; int /*<<< orphan*/  pdev; struct pnv_phb* phb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pnv_ioda_pe*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pnv_ioda_free_pe(struct pnv_ioda_pe *pe)
{
	struct pnv_phb *phb = pe->phb;
	unsigned int pe_num = pe->pe_number;

	WARN_ON(pe->pdev);
	WARN_ON(pe->npucomp); /* NPUs are not supposed to be freed */
	kfree(pe->npucomp);
	memset(pe, 0, sizeof(struct pnv_ioda_pe));
	clear_bit(pe_num, phb->ioda.pe_alloc);
}