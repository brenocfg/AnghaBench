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

/* Variables and functions */
 int /*<<< orphan*/  AA_DMMU_SCXR ; 
 int /*<<< orphan*/  ASI_DMMU ; 
 int /*<<< orphan*/  KERNBASE ; 
 int TLB_CTX_KERNEL ; 
 int TLB_CXR_PGSZ_MASK ; 
 int /*<<< orphan*/  flush (int /*<<< orphan*/ ) ; 
 int ldxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
pmap_set_kctx(void)
{

	stxa(AA_DMMU_SCXR, ASI_DMMU, (ldxa(AA_DMMU_SCXR, ASI_DMMU) &
	    TLB_CXR_PGSZ_MASK) | TLB_CTX_KERNEL);
	flush(KERNBASE);
}