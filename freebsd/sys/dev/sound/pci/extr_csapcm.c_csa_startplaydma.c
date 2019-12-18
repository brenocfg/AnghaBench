#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_2__ {int dma; } ;
struct csa_info {int pctl; TYPE_1__ pch; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA1_PCTL ; 
 int /*<<< orphan*/  BA1_PVOL ; 
 int csa_readmem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
csa_startplaydma(struct csa_info *csa)
{
	csa_res *resp;
	u_long ul;

	if (!csa->pch.dma) {
		resp = &csa->res;
		ul = csa_readmem(resp, BA1_PCTL);
		ul &= 0x0000ffff;
		csa_writemem(resp, BA1_PCTL, ul | csa->pctl);
		csa_writemem(resp, BA1_PVOL, 0x80008000);
		csa->pch.dma = 1;
	}
}