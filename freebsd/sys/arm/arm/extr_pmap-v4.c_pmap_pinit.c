#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_9__ {int resident_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  pv_pa; } ;
struct TYPE_7__ {TYPE_6__ pm_stats; int /*<<< orphan*/  pm_pvlist; int /*<<< orphan*/  pm_active; TYPE_6__* pm_l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ KERNBASE ; 
 int /*<<< orphan*/  PDEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int PMAP_ENTER_WIRED ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int VM_PROT_READ ; 
 int /*<<< orphan*/  bzero (TYPE_6__*,int) ; 
 int /*<<< orphan*/  pmap_alloc_l1 (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_enter (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_2__ systempage ; 
 scalar_t__ vector_page ; 

int
pmap_pinit(pmap_t pmap)
{
	PDEBUG(1, printf("pmap_pinit: pmap = %08x\n", (uint32_t) pmap));

	pmap_alloc_l1(pmap);
	bzero(pmap->pm_l2, sizeof(pmap->pm_l2));

	CPU_ZERO(&pmap->pm_active);

	TAILQ_INIT(&pmap->pm_pvlist);
	bzero(&pmap->pm_stats, sizeof pmap->pm_stats);
	pmap->pm_stats.resident_count = 1;
	if (vector_page < KERNBASE) {
		pmap_enter(pmap, vector_page, PHYS_TO_VM_PAGE(systempage.pv_pa),
		    VM_PROT_READ, PMAP_ENTER_WIRED | VM_PROT_READ, 0);
	}
	return (1);
}