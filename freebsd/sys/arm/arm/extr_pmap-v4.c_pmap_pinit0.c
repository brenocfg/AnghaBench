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
typedef  int u_int32_t ;
struct pmap {int /*<<< orphan*/  pm_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK_INIT (struct pmap*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct pmap*,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void
pmap_pinit0(struct pmap *pmap)
{
	PDEBUG(1, printf("pmap_pinit0: pmap = %08x\n", (u_int32_t) pmap));

	bcopy(kernel_pmap, pmap, sizeof(*pmap));
	bzero(&pmap->pm_mtx, sizeof(pmap->pm_mtx));
	PMAP_LOCK_INIT(pmap);
}