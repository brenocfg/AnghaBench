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
typedef  int u_int32_t ;
struct bfe_softc {int dummy; } ;

/* Variables and functions */
 int BFE_CLOCK ; 
 int BFE_FGC ; 
 int BFE_IBE ; 
 int BFE_RESET ; 
 int /*<<< orphan*/  BFE_SBIMSTATE ; 
 int /*<<< orphan*/  BFE_SBTMSHIGH ; 
 int /*<<< orphan*/  BFE_SBTMSLOW ; 
 int BFE_SERR ; 
 int BFE_TO ; 
 int CSR_READ_4 (struct bfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bfe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bfe_core_disable (struct bfe_softc*) ; 

__attribute__((used)) static void
bfe_core_reset(struct bfe_softc *sc)
{
	u_int32_t val;

	/* Disable the core */
	bfe_core_disable(sc);

	/* and bring it back up */
	CSR_WRITE_4(sc, BFE_SBTMSLOW, (BFE_RESET | BFE_CLOCK | BFE_FGC));
	CSR_READ_4(sc, BFE_SBTMSLOW);
	DELAY(10);

	/* Chip bug, clear SERR, IB and TO if they are set. */
	if (CSR_READ_4(sc, BFE_SBTMSHIGH) & BFE_SERR)
		CSR_WRITE_4(sc, BFE_SBTMSHIGH, 0);
	val = CSR_READ_4(sc, BFE_SBIMSTATE);
	if (val & (BFE_IBE | BFE_TO))
		CSR_WRITE_4(sc, BFE_SBIMSTATE, val & ~(BFE_IBE | BFE_TO));

	/* Clear reset and allow it to move through the core */
	CSR_WRITE_4(sc, BFE_SBTMSLOW, (BFE_CLOCK | BFE_FGC));
	CSR_READ_4(sc, BFE_SBTMSLOW);
	DELAY(10);

	/* Leave the clock set */
	CSR_WRITE_4(sc, BFE_SBTMSLOW, BFE_CLOCK);
	CSR_READ_4(sc, BFE_SBTMSLOW);
	DELAY(10);
}