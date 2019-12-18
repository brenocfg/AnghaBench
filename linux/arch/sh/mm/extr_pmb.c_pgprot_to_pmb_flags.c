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
typedef  int u64 ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long PMB_C ; 
 unsigned long PMB_UB ; 
 unsigned long PMB_WT ; 
 int _PAGE_CACHABLE ; 
 int _PAGE_WT ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long pgprot_to_pmb_flags(pgprot_t prot)
{
	unsigned long pmb_flags = 0;
	u64 flags = pgprot_val(prot);

	if (flags & _PAGE_CACHABLE)
		pmb_flags |= PMB_C;
	if (flags & _PAGE_WT)
		pmb_flags |= PMB_WT | PMB_UB;

	return pmb_flags;
}