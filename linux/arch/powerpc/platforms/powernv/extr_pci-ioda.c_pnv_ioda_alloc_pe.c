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
struct TYPE_2__ {int total_pe_num; int /*<<< orphan*/  pe_alloc; } ;
struct pnv_phb {TYPE_1__ ioda; } ;
struct pnv_ioda_pe {int dummy; } ;

/* Variables and functions */
 struct pnv_ioda_pe* pnv_ioda_init_pe (struct pnv_phb*,long) ; 
 int /*<<< orphan*/  test_and_set_bit (long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pnv_ioda_pe *pnv_ioda_alloc_pe(struct pnv_phb *phb)
{
	long pe;

	for (pe = phb->ioda.total_pe_num - 1; pe >= 0; pe--) {
		if (!test_and_set_bit(pe, phb->ioda.pe_alloc))
			return pnv_ioda_init_pe(phb, pe);
	}

	return NULL;
}