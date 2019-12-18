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
struct jme_softc {int dummy; } ;
typedef  int /*<<< orphan*/  map ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ JME_MSINUM_BASE ; 
 int JME_MSI_MESSAGES ; 
 int /*<<< orphan*/  MSINUM_INTR_SOURCE (int,int /*<<< orphan*/ ) ; 
 int MSINUM_NUM_INTR_SOURCE ; 
 size_t MSINUM_REG_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_INTR_RXQ0_COAL ; 
 int /*<<< orphan*/  N_INTR_RXQ0_COAL_TO ; 
 int /*<<< orphan*/  N_INTR_RXQ0_COMP ; 
 int /*<<< orphan*/  N_INTR_RXQ0_DESC_EMPTY ; 
 int /*<<< orphan*/  N_INTR_RXQ1_COAL ; 
 int /*<<< orphan*/  N_INTR_RXQ1_COAL_TO ; 
 int /*<<< orphan*/  N_INTR_RXQ1_COMP ; 
 int /*<<< orphan*/  N_INTR_RXQ1_DESC_EMPTY ; 
 int /*<<< orphan*/  N_INTR_RXQ2_COAL ; 
 int /*<<< orphan*/  N_INTR_RXQ2_COAL_TO ; 
 int /*<<< orphan*/  N_INTR_RXQ2_COMP ; 
 int /*<<< orphan*/  N_INTR_RXQ2_DESC_EMPTY ; 
 int /*<<< orphan*/  N_INTR_RXQ3_COAL ; 
 int /*<<< orphan*/  N_INTR_RXQ3_COAL_TO ; 
 int /*<<< orphan*/  N_INTR_RXQ3_COMP ; 
 int /*<<< orphan*/  N_INTR_RXQ3_DESC_EMPTY ; 
 int /*<<< orphan*/  N_INTR_TXQ0_COMP ; 
 int /*<<< orphan*/  N_INTR_TXQ1_COMP ; 
 int /*<<< orphan*/  N_INTR_TXQ2_COMP ; 
 int /*<<< orphan*/  N_INTR_TXQ3_COMP ; 
 int /*<<< orphan*/  N_INTR_TXQ4_COMP ; 
 int /*<<< orphan*/  N_INTR_TXQ5_COMP ; 
 int /*<<< orphan*/  N_INTR_TXQ6_COMP ; 
 int /*<<< orphan*/  N_INTR_TXQ7_COMP ; 
 int /*<<< orphan*/  N_INTR_TXQ_COAL ; 
 int /*<<< orphan*/  N_INTR_TXQ_COAL_TO ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
jme_map_intr_vector(struct jme_softc *sc)
{
	uint32_t map[MSINUM_NUM_INTR_SOURCE / JME_MSI_MESSAGES];

	bzero(map, sizeof(map));

	/* Map Tx interrupts source to MSI/MSIX vector 2. */
	map[MSINUM_REG_INDEX(N_INTR_TXQ0_COMP)] =
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ0_COMP);
	map[MSINUM_REG_INDEX(N_INTR_TXQ1_COMP)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ1_COMP);
	map[MSINUM_REG_INDEX(N_INTR_TXQ2_COMP)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ2_COMP);
	map[MSINUM_REG_INDEX(N_INTR_TXQ3_COMP)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ3_COMP);
	map[MSINUM_REG_INDEX(N_INTR_TXQ4_COMP)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ4_COMP);
	map[MSINUM_REG_INDEX(N_INTR_TXQ5_COMP)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ5_COMP);
	map[MSINUM_REG_INDEX(N_INTR_TXQ6_COMP)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ6_COMP);
	map[MSINUM_REG_INDEX(N_INTR_TXQ7_COMP)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ7_COMP);
	map[MSINUM_REG_INDEX(N_INTR_TXQ_COAL)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ_COAL);
	map[MSINUM_REG_INDEX(N_INTR_TXQ_COAL_TO)] |=
	    MSINUM_INTR_SOURCE(2, N_INTR_TXQ_COAL_TO);

	/* Map Rx interrupts source to MSI/MSIX vector 1. */
	map[MSINUM_REG_INDEX(N_INTR_RXQ0_COMP)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ0_COMP);
	map[MSINUM_REG_INDEX(N_INTR_RXQ1_COMP)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ1_COMP);
	map[MSINUM_REG_INDEX(N_INTR_RXQ2_COMP)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ2_COMP);
	map[MSINUM_REG_INDEX(N_INTR_RXQ3_COMP)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ3_COMP);
	map[MSINUM_REG_INDEX(N_INTR_RXQ0_DESC_EMPTY)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ0_DESC_EMPTY);
	map[MSINUM_REG_INDEX(N_INTR_RXQ1_DESC_EMPTY)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ1_DESC_EMPTY);
	map[MSINUM_REG_INDEX(N_INTR_RXQ2_DESC_EMPTY)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ2_DESC_EMPTY);
	map[MSINUM_REG_INDEX(N_INTR_RXQ3_DESC_EMPTY)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ3_DESC_EMPTY);
	map[MSINUM_REG_INDEX(N_INTR_RXQ0_COAL)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ0_COAL);
	map[MSINUM_REG_INDEX(N_INTR_RXQ1_COAL)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ1_COAL);
	map[MSINUM_REG_INDEX(N_INTR_RXQ2_COAL)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ2_COAL);
	map[MSINUM_REG_INDEX(N_INTR_RXQ3_COAL)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ3_COAL);
	map[MSINUM_REG_INDEX(N_INTR_RXQ0_COAL_TO)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ0_COAL_TO);
	map[MSINUM_REG_INDEX(N_INTR_RXQ1_COAL_TO)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ1_COAL_TO);
	map[MSINUM_REG_INDEX(N_INTR_RXQ2_COAL_TO)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ2_COAL_TO);
	map[MSINUM_REG_INDEX(N_INTR_RXQ3_COAL_TO)] =
	    MSINUM_INTR_SOURCE(1, N_INTR_RXQ3_COAL_TO);

	/* Map all other interrupts source to MSI/MSIX vector 0. */
	CSR_WRITE_4(sc, JME_MSINUM_BASE + sizeof(uint32_t) * 0, map[0]);
	CSR_WRITE_4(sc, JME_MSINUM_BASE + sizeof(uint32_t) * 1, map[1]);
	CSR_WRITE_4(sc, JME_MSINUM_BASE + sizeof(uint32_t) * 2, map[2]);
	CSR_WRITE_4(sc, JME_MSINUM_BASE + sizeof(uint32_t) * 3, map[3]);
}