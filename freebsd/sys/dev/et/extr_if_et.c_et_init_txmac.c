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
struct et_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ET_TXMAC_CTRL ; 
 int ET_TXMAC_CTRL_ENABLE ; 
 int ET_TXMAC_CTRL_FC_DISABLE ; 
 int /*<<< orphan*/  ET_TXMAC_FLOWCTRL ; 
 int ET_TXMAC_FLOWCTRL_CFPT_SHIFT ; 

__attribute__((used)) static void
et_init_txmac(struct et_softc *sc)
{

	/* Disable TX MAC and FC(?) */
	CSR_WRITE_4(sc, ET_TXMAC_CTRL, ET_TXMAC_CTRL_FC_DISABLE);

	/*
	 * Initialize pause time.
	 * This register should be set before XON/XOFF frame is
	 * sent by driver.
	 */
	CSR_WRITE_4(sc, ET_TXMAC_FLOWCTRL, 0 << ET_TXMAC_FLOWCTRL_CFPT_SHIFT);

	/* Enable TX MAC but leave FC(?) diabled */
	CSR_WRITE_4(sc, ET_TXMAC_CTRL,
		    ET_TXMAC_CTRL_ENABLE | ET_TXMAC_CTRL_FC_DISABLE);
}