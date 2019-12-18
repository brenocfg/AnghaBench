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
typedef  int uint32_t ;
struct amdtemp_softc {int sc_flags; int sc_offset; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int amdsensor_t ;

/* Variables and functions */
 int AMDTEMP_FLAG_ALT_OFFSET ; 
 int AMDTEMP_FLAG_CS_SWAP ; 
 int AMDTEMP_FLAG_CT_10BIT ; 
 int /*<<< orphan*/  AMDTEMP_THERMTP_STAT ; 
 int AMDTEMP_TTSR_SELCORE ; 
 int AMDTEMP_TTSR_SELSENSOR ; 
 scalar_t__ AMDTEMP_ZERO_C_TO_K ; 
#define  CORE0 133 
#define  CORE0_SENSOR0 132 
#define  CORE0_SENSOR1 131 
#define  CORE1 130 
#define  CORE1_SENSOR0 129 
#define  CORE1_SENSOR1 128 
 struct amdtemp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int32_t
amdtemp_gettemp0f(device_t dev, amdsensor_t sensor)
{
	struct amdtemp_softc *sc = device_get_softc(dev);
	uint32_t mask, offset, temp;

	/* Set Sensor/Core selector. */
	temp = pci_read_config(dev, AMDTEMP_THERMTP_STAT, 1);
	temp &= ~(AMDTEMP_TTSR_SELCORE | AMDTEMP_TTSR_SELSENSOR);
	switch (sensor) {
	case CORE0_SENSOR1:
		temp |= AMDTEMP_TTSR_SELSENSOR;
		/* FALLTHROUGH */
	case CORE0_SENSOR0:
	case CORE0:
		if ((sc->sc_flags & AMDTEMP_FLAG_CS_SWAP) != 0)
			temp |= AMDTEMP_TTSR_SELCORE;
		break;
	case CORE1_SENSOR1:
		temp |= AMDTEMP_TTSR_SELSENSOR;
		/* FALLTHROUGH */
	case CORE1_SENSOR0:
	case CORE1:
		if ((sc->sc_flags & AMDTEMP_FLAG_CS_SWAP) == 0)
			temp |= AMDTEMP_TTSR_SELCORE;
		break;
	}
	pci_write_config(dev, AMDTEMP_THERMTP_STAT, temp, 1);

	mask = (sc->sc_flags & AMDTEMP_FLAG_CT_10BIT) != 0 ? 0x3ff : 0x3fc;
	offset = (sc->sc_flags & AMDTEMP_FLAG_ALT_OFFSET) != 0 ? 28 : 49;
	temp = pci_read_config(dev, AMDTEMP_THERMTP_STAT, 4);
	temp = ((temp >> 14) & mask) * 5 / 2;
	temp += AMDTEMP_ZERO_C_TO_K + (sc->sc_offset - offset) * 10;

	return (temp);
}