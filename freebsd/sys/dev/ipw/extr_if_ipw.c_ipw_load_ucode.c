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
struct ipw_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct ipw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  IPW_CSR_RST ; 
 int MEM_READ_1 (struct ipw_softc*,int) ; 
 int /*<<< orphan*/  MEM_WRITE_1 (struct ipw_softc*,int,int) ; 
 int /*<<< orphan*/  MEM_WRITE_2 (struct ipw_softc*,int,int) ; 
 int /*<<< orphan*/  MEM_WRITE_4 (struct ipw_softc*,int,int) ; 
 int /*<<< orphan*/  MEM_WRITE_MULTI_1 (struct ipw_softc*,int,char const*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ipw_load_ucode(struct ipw_softc *sc, const char *uc, int size)
{
	int ntries;

	MEM_WRITE_4(sc, 0x3000e0, 0x80000000);
	CSR_WRITE_4(sc, IPW_CSR_RST, 0);

	MEM_WRITE_2(sc, 0x220000, 0x0703);
	MEM_WRITE_2(sc, 0x220000, 0x0707);

	MEM_WRITE_1(sc, 0x210014, 0x72);
	MEM_WRITE_1(sc, 0x210014, 0x72);

	MEM_WRITE_1(sc, 0x210000, 0x40);
	MEM_WRITE_1(sc, 0x210000, 0x00);
	MEM_WRITE_1(sc, 0x210000, 0x40);

	MEM_WRITE_MULTI_1(sc, 0x210010, uc, size);

	MEM_WRITE_1(sc, 0x210000, 0x00);
	MEM_WRITE_1(sc, 0x210000, 0x00);
	MEM_WRITE_1(sc, 0x210000, 0x80);

	MEM_WRITE_2(sc, 0x220000, 0x0703);
	MEM_WRITE_2(sc, 0x220000, 0x0707);

	MEM_WRITE_1(sc, 0x210014, 0x72);
	MEM_WRITE_1(sc, 0x210014, 0x72);

	MEM_WRITE_1(sc, 0x210000, 0x00);
	MEM_WRITE_1(sc, 0x210000, 0x80);

	for (ntries = 0; ntries < 10; ntries++) {
		if (MEM_READ_1(sc, 0x210000) & 1)
			break;
		DELAY(10);
	}
	if (ntries == 10) {
		device_printf(sc->sc_dev,
		    "timeout waiting for ucode to initialize\n");
		return EIO;
	}

	MEM_WRITE_4(sc, 0x3000e0, 0);

	return 0;
}