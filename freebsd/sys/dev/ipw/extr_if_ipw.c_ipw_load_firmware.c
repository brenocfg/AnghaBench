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
typedef  char uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ipw_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ipw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ipw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GETLE16 (char const*) ; 
 int GETLE32 (char const*) ; 
 int /*<<< orphan*/  IPW_CSR_CTL ; 
 int /*<<< orphan*/  IPW_CSR_INTR_MASK ; 
 int /*<<< orphan*/  IPW_CSR_IO ; 
 int /*<<< orphan*/  IPW_CSR_RST ; 
 int IPW_CTL_ALLOW_STANDBY ; 
 int IPW_INTR_MASK ; 
 int IPW_IO_GPIO1_ENABLE ; 
 int IPW_IO_GPIO1_MASK ; 
 int IPW_IO_GPIO3_MASK ; 
 int IPW_IO_LED_OFF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ipw_write_mem_1 (struct ipw_softc*,int,char const*,int /*<<< orphan*/ ) ; 
 int msleep (struct ipw_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipw_load_firmware(struct ipw_softc *sc, const char *fw, int size)
{
	const uint8_t *p, *end;
	uint32_t tmp, dst;
	uint16_t len;
	int error;

	p = fw;
	end = fw + size;
	while (p < end) {
		dst = GETLE32(p); p += 4;
		len = GETLE16(p); p += 2;

		ipw_write_mem_1(sc, dst, p, len);
		p += len;
	}

	CSR_WRITE_4(sc, IPW_CSR_IO, IPW_IO_GPIO1_ENABLE | IPW_IO_GPIO3_MASK |
	    IPW_IO_LED_OFF);

	/* enable interrupts */
	CSR_WRITE_4(sc, IPW_CSR_INTR_MASK, IPW_INTR_MASK);

	/* kick the firmware */
	CSR_WRITE_4(sc, IPW_CSR_RST, 0);

	tmp = CSR_READ_4(sc, IPW_CSR_CTL);
	CSR_WRITE_4(sc, IPW_CSR_CTL, tmp | IPW_CTL_ALLOW_STANDBY);

	/* wait at most one second for firmware initialization to complete */
	if ((error = msleep(sc, &sc->sc_mtx, 0, "ipwinit", hz)) != 0) {
		device_printf(sc->sc_dev, "timeout waiting for firmware "
		    "initialization to complete\n");
		return error;
	}

	tmp = CSR_READ_4(sc, IPW_CSR_IO);
	CSR_WRITE_4(sc, IPW_CSR_IO, tmp | IPW_IO_GPIO1_MASK |
	    IPW_IO_GPIO3_MASK);

	return 0;
}