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
typedef  int /*<<< orphan*/  vm_pindex_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_NPTEPG ; 

vm_pindex_t
pglvl_max_pages(int pglvl)
{
	vm_pindex_t res;
	int i;

	for (res = 0, i = pglvl; i > 0; i--) {
		res *= DMAR_NPTEPG;
		res++;
	}
	return (res);
}