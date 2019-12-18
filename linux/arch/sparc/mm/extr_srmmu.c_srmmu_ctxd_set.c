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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  ctxd_t ;

/* Variables and functions */
 int SRMMU_ET_PTD ; 
 int __nocache_pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pte (int) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void srmmu_ctxd_set(ctxd_t *ctxp, pgd_t *pgdp)
{
	pte_t pte;

	pte = __pte((SRMMU_ET_PTD | (__nocache_pa(pgdp) >> 4)));
	set_pte((pte_t *)ctxp, pte);
}