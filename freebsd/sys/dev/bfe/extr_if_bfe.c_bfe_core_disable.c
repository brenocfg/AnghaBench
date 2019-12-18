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
struct bfe_softc {int dummy; } ;

/* Variables and functions */
 int BFE_BUSY ; 
 int BFE_CLOCK ; 
 int BFE_FGC ; 
 int BFE_REJECT ; 
 int BFE_RESET ; 
 int /*<<< orphan*/  BFE_SBTMSHIGH ; 
 int /*<<< orphan*/  BFE_SBTMSLOW ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bfe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bfe_wait_bit (struct bfe_softc*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
bfe_core_disable(struct bfe_softc *sc)
{
	if ((CSR_READ_4(sc, BFE_SBTMSLOW)) & BFE_RESET)
		return;

	/*
	 * Set reject, wait for it set, then wait for the core to stop
	 * being busy, then set reset and reject and enable the clocks.
	 */
	CSR_WRITE_4(sc, BFE_SBTMSLOW, (BFE_REJECT | BFE_CLOCK));
	bfe_wait_bit(sc, BFE_SBTMSLOW, BFE_REJECT, 1000, 0);
	bfe_wait_bit(sc, BFE_SBTMSHIGH, BFE_BUSY, 1000, 1);
	CSR_WRITE_4(sc, BFE_SBTMSLOW, (BFE_FGC | BFE_CLOCK | BFE_REJECT |
				BFE_RESET));
	CSR_READ_4(sc, BFE_SBTMSLOW);
	DELAY(10);
	/* Leave reset and reject set */
	CSR_WRITE_4(sc, BFE_SBTMSLOW, (BFE_REJECT | BFE_RESET));
	DELAY(10);
}