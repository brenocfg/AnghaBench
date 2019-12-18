#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_4__ {int /*<<< orphan*/  pm_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  curpmap ; 

void
pmap_activate_boot(pmap_t pmap)
{
	u_int hart;

	hart = PCPU_GET(hart);
#ifdef SMP
	CPU_SET_ATOMIC(hart, &pmap->pm_active);
#else
	CPU_SET(hart, &pmap->pm_active);
#endif
	PCPU_SET(curpmap, pmap);
}