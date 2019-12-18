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
typedef  int /*<<< orphan*/  uint8_t ;
struct nct_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * iores; } ;
typedef  int /*<<< orphan*/  reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  nct_get_ioreg (struct nct_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nct_io_write (struct nct_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nct_write_reg(struct nct_softc *sc, reg_t reg, int group, uint8_t val)
{
	uint8_t ioreg;

	ioreg = nct_get_ioreg(sc, reg, group);
	if (sc->iores != NULL)
		nct_io_write(sc, group, ioreg, val);
	else
		superio_write(sc->dev, ioreg, val);
}