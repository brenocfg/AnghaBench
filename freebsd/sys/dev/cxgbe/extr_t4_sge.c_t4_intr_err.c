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
typedef  int uint32_t ;
struct adapter {int debug_flags; int flags; int /*<<< orphan*/  swintr; } ;

/* Variables and functions */
 int ADAP_ERR ; 
 int /*<<< orphan*/  A_PL_PF_INT_CAUSE ; 
 int DF_VERBOSE_SLOWINTR ; 
 int F_PFSW ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_slow_intr_handler (struct adapter*,int const) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void
t4_intr_err(void *arg)
{
	struct adapter *sc = arg;
	uint32_t v;
	const bool verbose = (sc->debug_flags & DF_VERBOSE_SLOWINTR) != 0;

	if (sc->flags & ADAP_ERR)
		return;

	v = t4_read_reg(sc, MYPF_REG(A_PL_PF_INT_CAUSE));
	if (v & F_PFSW) {
		sc->swintr++;
		t4_write_reg(sc, MYPF_REG(A_PL_PF_INT_CAUSE), v);
	}

	t4_slow_intr_handler(sc, verbose);
}