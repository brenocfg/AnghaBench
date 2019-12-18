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
 int /*<<< orphan*/  BFE_DMARX_CTRL ; 
 int /*<<< orphan*/  BFE_DMATX_CTRL ; 
 int /*<<< orphan*/  BFE_ENET_CTRL ; 
 int /*<<< orphan*/  BFE_ENET_DISABLE ; 
 int /*<<< orphan*/  BFE_IMASK ; 
 int /*<<< orphan*/  BFE_LOCK_ASSERT (struct bfe_softc*) ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bfe_wait_bit (struct bfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bfe_chip_halt(struct bfe_softc *sc)
{
	BFE_LOCK_ASSERT(sc);
	/* disable interrupts - not that it actually does..*/
	CSR_WRITE_4(sc, BFE_IMASK, 0);
	CSR_READ_4(sc, BFE_IMASK);

	CSR_WRITE_4(sc, BFE_ENET_CTRL, BFE_ENET_DISABLE);
	bfe_wait_bit(sc, BFE_ENET_CTRL, BFE_ENET_DISABLE, 200, 1);

	CSR_WRITE_4(sc, BFE_DMARX_CTRL, 0);
	CSR_WRITE_4(sc, BFE_DMATX_CTRL, 0);
	DELAY(10);
}