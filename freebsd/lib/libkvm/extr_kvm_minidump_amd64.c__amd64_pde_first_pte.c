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
typedef  int u_long ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  amd64_pte_t ;
typedef  int /*<<< orphan*/  amd64_pde_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_PAGE_SIZE ; 
 int AMD64_PG_FRAME ; 
 int /*<<< orphan*/ * _kvm_map_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int* _kvm_pmap_get (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static amd64_pte_t *
_amd64_pde_first_pte(kvm_t *kd, u_long pdeindex)
{
	u_long *pa;

	pa = _kvm_pmap_get(kd, pdeindex, sizeof(amd64_pde_t));
	if (pa == NULL)
		return NULL;
	return _kvm_map_get(kd, *pa & AMD64_PG_FRAME, AMD64_PAGE_SIZE);
}