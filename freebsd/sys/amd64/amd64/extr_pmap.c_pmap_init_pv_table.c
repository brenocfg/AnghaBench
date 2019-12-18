#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
struct md_page {int /*<<< orphan*/  pv_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NBPDR ; 
 long NPV_LIST_LOCKS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 long howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kmem_malloc (int,int) ; 
 TYPE_2__ pv_dummy ; 
 int /*<<< orphan*/ * pv_list_locks ; 
 struct md_page* pv_table ; 
 int round_page (int) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int vm_phys_nsegs ; 
 TYPE_1__* vm_phys_segs ; 

__attribute__((used)) static void
pmap_init_pv_table(void)
{
	vm_size_t s;
	long i, pv_npg;

	/*
	 * Initialize the pool of pv list locks.
	 */
	for (i = 0; i < NPV_LIST_LOCKS; i++)
		rw_init(&pv_list_locks[i], "pmap pv list");

	/*
	 * Calculate the size of the pv head table for superpages.
	 */
	pv_npg = howmany(vm_phys_segs[vm_phys_nsegs - 1].end, NBPDR);

	/*
	 * Allocate memory for the pv head table for superpages.
	 */
	s = (vm_size_t)pv_npg * sizeof(struct md_page);
	s = round_page(s);
	pv_table = (struct md_page *)kmem_malloc(s, M_WAITOK | M_ZERO);
	for (i = 0; i < pv_npg; i++)
		TAILQ_INIT(&pv_table[i].pv_list);
	TAILQ_INIT(&pv_dummy.pv_list);
}