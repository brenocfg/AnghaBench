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
struct TYPE_2__ {scalar_t__ allow_gmap_hpage_1m; int /*<<< orphan*/  asce; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDTE_GLOBAL ; 
 int IDTE_GUEST_ASCE ; 
 int IDTE_NODAT ; 
 scalar_t__ MACHINE_HAS_IDTE ; 
 scalar_t__ MACHINE_HAS_TLB_GUEST ; 
 int /*<<< orphan*/  __pmdp_csp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pmdp_idte (unsigned long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmap_pmdp_csp (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  gmap_pmdp_idte_global (struct mm_struct*,unsigned long) ; 
 scalar_t__ mm_has_pgste (struct mm_struct*) ; 

__attribute__((used)) static inline void pmdp_idte_global(struct mm_struct *mm,
				    unsigned long addr, pmd_t *pmdp)
{
	if (MACHINE_HAS_TLB_GUEST) {
		__pmdp_idte(addr, pmdp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_GLOBAL);
		if (mm_has_pgste(mm) && mm->context.allow_gmap_hpage_1m)
			gmap_pmdp_idte_global(mm, addr);
	} else if (MACHINE_HAS_IDTE) {
		__pmdp_idte(addr, pmdp, 0, 0, IDTE_GLOBAL);
		if (mm_has_pgste(mm) && mm->context.allow_gmap_hpage_1m)
			gmap_pmdp_idte_global(mm, addr);
	} else {
		__pmdp_csp(pmdp);
		if (mm_has_pgste(mm) && mm->context.allow_gmap_hpage_1m)
			gmap_pmdp_csp(mm, addr);
	}
}