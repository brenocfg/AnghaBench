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
struct sge_iq {int dummy; } ;
struct TYPE_2__ {struct sge_iq fwq; } ;
struct adapter {int intr_count; scalar_t__ intr_type; TYPE_1__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_PF_CLI ; 
 scalar_t__ INTR_INTX ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_intr_err (void*) ; 
 int /*<<< orphan*/  t4_intr_evt (struct sge_iq*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
t4_intr_all(void *arg)
{
	struct adapter *sc = arg;
	struct sge_iq *fwq = &sc->sge.fwq;

	MPASS(sc->intr_count == 1);

	if (sc->intr_type == INTR_INTX)
		t4_write_reg(sc, MYPF_REG(A_PCIE_PF_CLI), 0);

	t4_intr_err(arg);
	t4_intr_evt(fwq);
}