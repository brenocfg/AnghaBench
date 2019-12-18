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
struct cpa_data {unsigned int numpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cpa_addr (struct cpa_data*,unsigned int) ; 
 int /*<<< orphan*/  __flush_tlb_one_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fix_addr (int /*<<< orphan*/ ) ; 

void __cpa_flush_tlb(void *data)
{
	struct cpa_data *cpa = data;
	unsigned int i;

	for (i = 0; i < cpa->numpages; i++)
		__flush_tlb_one_kernel(fix_addr(__cpa_addr(cpa, i)));
}