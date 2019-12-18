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
typedef  scalar_t__ uint32_t ;
struct bfe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_LOCK_ASSERT (struct bfe_softc*) ; 
 int /*<<< orphan*/  BFE_MIB_CLR_ON_READ ; 
 int /*<<< orphan*/  BFE_MIB_CTRL ; 
 scalar_t__ BFE_RX_GOOD_O ; 
 scalar_t__ BFE_RX_NPAUSE ; 
 scalar_t__ BFE_TX_GOOD_O ; 
 scalar_t__ BFE_TX_PAUSE ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bfe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfe_clear_stats(struct bfe_softc *sc)
{
	uint32_t reg;

	BFE_LOCK_ASSERT(sc);

	CSR_WRITE_4(sc, BFE_MIB_CTRL, BFE_MIB_CLR_ON_READ);
	for (reg = BFE_TX_GOOD_O; reg <= BFE_TX_PAUSE; reg += 4)
		CSR_READ_4(sc, reg);
	for (reg = BFE_RX_GOOD_O; reg <= BFE_RX_NPAUSE; reg += 4)
		CSR_READ_4(sc, reg);
}