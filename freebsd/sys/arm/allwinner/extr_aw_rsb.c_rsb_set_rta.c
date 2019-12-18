#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct rsb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ rta; int addr; } ;

/* Variables and functions */
 int CMD_SRTA ; 
 int DAR_DA_SHIFT ; 
 int DAR_RTA_SHIFT ; 
 int ENXIO ; 
 int /*<<< orphan*/  RSB_ASSERT_LOCKED (struct rsb_softc*) ; 
 int /*<<< orphan*/  RSB_CMD ; 
 int /*<<< orphan*/  RSB_DAR ; 
 int /*<<< orphan*/  RSB_INTS ; 
 int RSB_READ (struct rsb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSB_WRITE (struct rsb_softc*,int /*<<< orphan*/ ,int) ; 
 struct rsb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* rsb_rtamap ; 
 int rsb_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rsb_set_rta(device_t dev, uint16_t addr)
{
	struct rsb_softc *sc;
	uint8_t rta;
	int i;

	sc = device_get_softc(dev);

	RSB_ASSERT_LOCKED(sc);

	/* Lookup run-time address for given device address */
	for (rta = 0, i = 0; rsb_rtamap[i].rta != 0; i++)
		if (rsb_rtamap[i].addr == addr) {
			rta = rsb_rtamap[i].rta;
			break;
		}
	if (rta == 0) {
		device_printf(dev, "RTA not known for address %#x\n", addr);
		return (ENXIO);
	}

	/* Set run-time address */
	RSB_WRITE(sc, RSB_INTS, RSB_READ(sc, RSB_INTS));
	RSB_WRITE(sc, RSB_DAR, (addr << DAR_DA_SHIFT) | (rta << DAR_RTA_SHIFT));
	RSB_WRITE(sc, RSB_CMD, CMD_SRTA);

	return (rsb_start(dev));
}