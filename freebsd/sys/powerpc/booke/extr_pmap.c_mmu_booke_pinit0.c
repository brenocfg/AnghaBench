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
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curpmap ; 
 int /*<<< orphan*/  mmu_booke_pinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmu_booke_pinit0(mmu_t mmu, pmap_t pmap)
{

	PMAP_LOCK_INIT(pmap);
	mmu_booke_pinit(mmu, pmap);
	PCPU_SET(curpmap, pmap);
}