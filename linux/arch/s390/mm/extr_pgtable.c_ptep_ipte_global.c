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
struct TYPE_2__ {unsigned long asce; int /*<<< orphan*/  gmap_asce; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPTE_GLOBAL ; 
 unsigned long IPTE_GUEST_ASCE ; 
 unsigned long IPTE_NODAT ; 
 scalar_t__ MACHINE_HAS_TLB_GUEST ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ptep_ipte (unsigned long,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ptep_ipte_global(struct mm_struct *mm, unsigned long addr,
				    pte_t *ptep, int nodat)
{
	unsigned long opt, asce;

	if (MACHINE_HAS_TLB_GUEST) {
		opt = 0;
		asce = READ_ONCE(mm->context.gmap_asce);
		if (asce == 0UL || nodat)
			opt |= IPTE_NODAT;
		if (asce != -1UL) {
			asce = asce ? : mm->context.asce;
			opt |= IPTE_GUEST_ASCE;
		}
		__ptep_ipte(addr, ptep, opt, asce, IPTE_GLOBAL);
	} else {
		__ptep_ipte(addr, ptep, 0, 0, IPTE_GLOBAL);
	}
}