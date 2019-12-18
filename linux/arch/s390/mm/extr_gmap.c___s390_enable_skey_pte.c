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
struct mm_walk {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptep_zap_key (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __s390_enable_skey_pte(pte_t *pte, unsigned long addr,
				  unsigned long next, struct mm_walk *walk)
{
	/* Clear storage key */
	ptep_zap_key(walk->mm, addr, pte);
	return 0;
}