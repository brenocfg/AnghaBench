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
struct dc_softc {int /*<<< orphan*/ * dc_srom; int /*<<< orphan*/  dc_dev; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int DC_ROM_SIZE (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  dc_read_eeprom (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dc_read_srom(struct dc_softc *sc, int bits)
{
	int size;

	size = DC_ROM_SIZE(bits);
	sc->dc_srom = malloc(size, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (sc->dc_srom == NULL) {
		device_printf(sc->dc_dev, "Could not allocate SROM buffer\n");
		return (ENOMEM);
	}
	dc_read_eeprom(sc, (caddr_t)sc->dc_srom, 0, (size / 2), 0);
	return (0);
}