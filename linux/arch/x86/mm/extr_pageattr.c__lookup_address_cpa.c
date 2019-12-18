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
struct cpa_data {scalar_t__ pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 int /*<<< orphan*/ * lookup_address_in_pgd (scalar_t__,unsigned long,unsigned int*) ; 
 scalar_t__ pgd_index (unsigned long) ; 

__attribute__((used)) static pte_t *_lookup_address_cpa(struct cpa_data *cpa, unsigned long address,
				  unsigned int *level)
{
	if (cpa->pgd)
		return lookup_address_in_pgd(cpa->pgd + pgd_index(address),
					       address, level);

	return lookup_address(address, level);
}