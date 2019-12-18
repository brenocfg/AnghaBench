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
struct sge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_4 (struct sge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  GMIIControl ; 
 int /*<<< orphan*/  IntrControl ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  RX_CTL ; 
 int /*<<< orphan*/  TX_CTL ; 

__attribute__((used)) static void
sge_reset(struct sge_softc *sc)
{

	CSR_WRITE_4(sc, IntrMask, 0);
	CSR_WRITE_4(sc, IntrStatus, 0xffffffff);

	/* Soft reset. */
	CSR_WRITE_4(sc, IntrControl, 0x8000);
	CSR_READ_4(sc, IntrControl);
	DELAY(100);
	CSR_WRITE_4(sc, IntrControl, 0);
	/* Stop MAC. */
	CSR_WRITE_4(sc, TX_CTL, 0x1a00);
	CSR_WRITE_4(sc, RX_CTL, 0x1a00);

	CSR_WRITE_4(sc, IntrMask, 0);
	CSR_WRITE_4(sc, IntrStatus, 0xffffffff);

	CSR_WRITE_4(sc, GMIIControl, 0);
}