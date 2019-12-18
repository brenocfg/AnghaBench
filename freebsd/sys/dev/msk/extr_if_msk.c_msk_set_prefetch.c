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
typedef  int /*<<< orphan*/  uint32_t ;
struct msk_softc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_4 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSK_ADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSK_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREF_UNIT_ADDR_HI_REG ; 
 int /*<<< orphan*/  PREF_UNIT_ADDR_LOW_REG ; 
 int /*<<< orphan*/  PREF_UNIT_CTRL_REG ; 
 int /*<<< orphan*/  PREF_UNIT_LAST_IDX_REG ; 
 int /*<<< orphan*/  PREF_UNIT_OP_ON ; 
 int /*<<< orphan*/  PREF_UNIT_RST_CLR ; 
 int /*<<< orphan*/  PREF_UNIT_RST_SET ; 
 int /*<<< orphan*/  Y2_PREF_Q_ADDR (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
msk_set_prefetch(struct msk_softc *sc, int qaddr, bus_addr_t addr,
    uint32_t count)
{

	/* Reset the prefetch unit. */
	CSR_WRITE_4(sc, Y2_PREF_Q_ADDR(qaddr, PREF_UNIT_CTRL_REG),
	    PREF_UNIT_RST_SET);
	CSR_WRITE_4(sc, Y2_PREF_Q_ADDR(qaddr, PREF_UNIT_CTRL_REG),
	    PREF_UNIT_RST_CLR);
	/* Set LE base address. */
	CSR_WRITE_4(sc, Y2_PREF_Q_ADDR(qaddr, PREF_UNIT_ADDR_LOW_REG),
	    MSK_ADDR_LO(addr));
	CSR_WRITE_4(sc, Y2_PREF_Q_ADDR(qaddr, PREF_UNIT_ADDR_HI_REG),
	    MSK_ADDR_HI(addr));
	/* Set the list last index. */
	CSR_WRITE_2(sc, Y2_PREF_Q_ADDR(qaddr, PREF_UNIT_LAST_IDX_REG),
	    count);
	/* Turn on prefetch unit. */
	CSR_WRITE_4(sc, Y2_PREF_Q_ADDR(qaddr, PREF_UNIT_CTRL_REG),
	    PREF_UNIT_OP_ON);
	/* Dummy read to ensure write. */
	CSR_READ_4(sc, Y2_PREF_Q_ADDR(qaddr, PREF_UNIT_CTRL_REG));
}