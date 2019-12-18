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
typedef  int u_long ;
struct TYPE_3__ {int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {scalar_t__ dma; } ;
struct csa_info {int pctl; TYPE_1__ rch; TYPE_2__ pch; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_SERBSP ; 
 int /*<<< orphan*/  BA1_PCTL ; 
 int /*<<< orphan*/  BA1_PVOL ; 
 int /*<<< orphan*/  csa_clearserialfifos (int /*<<< orphan*/ *) ; 
 int csa_readmem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writeio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
csa_stopplaydma(struct csa_info *csa)
{
	csa_res *resp;
	u_long ul;

	if (csa->pch.dma) {
		resp = &csa->res;
		ul = csa_readmem(resp, BA1_PCTL);
		csa->pctl = ul & 0xffff0000;
		csa_writemem(resp, BA1_PCTL, ul & 0x0000ffff);
		csa_writemem(resp, BA1_PVOL, 0xffffffff);
		csa->pch.dma = 0;

		/*
		 * The bitwise pointer of the serial FIFO in the DSP
		 * seems to make an error upon starting or stopping the
		 * DSP. Clear the FIFO and correct the pointer if we
		 * are not capturing.
		 */
		if (!csa->rch.dma) {
			csa_clearserialfifos(resp);
			csa_writeio(resp, BA0_SERBSP, 0);
		}
	}
}