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
typedef  int /*<<< orphan*/  uint16_t ;
struct iwi_softc {int /*<<< orphan*/  sc_dev; } ;
struct iwi_fw {char* data; size_t size; } ;

/* Variables and functions */
 int CSR_READ_4 (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct iwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  IWI_CSR_RST ; 
 int /*<<< orphan*/  IWI_LOCK_ASSERT (struct iwi_softc*) ; 
 int IWI_MEM_EEPROM_EVENT ; 
 int IWI_RST_MASTER_DISABLED ; 
 int IWI_RST_PRINCETON_RESET ; 
 int IWI_RST_STOP_MASTER ; 
 int MEM_READ_1 (struct iwi_softc*,int) ; 
 int /*<<< orphan*/  MEM_READ_4 (struct iwi_softc*,int) ; 
 int /*<<< orphan*/  MEM_WRITE_1 (struct iwi_softc*,int,int) ; 
 int /*<<< orphan*/  MEM_WRITE_2 (struct iwi_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_WRITE_4 (struct iwi_softc*,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
iwi_load_ucode(struct iwi_softc *sc, const struct iwi_fw *fw)
{
	uint32_t tmp;
	const uint16_t *w;
	const char *uc = fw->data;
	size_t size = fw->size;
	int i, ntries, error;

	IWI_LOCK_ASSERT(sc);
	error = 0;
	CSR_WRITE_4(sc, IWI_CSR_RST, CSR_READ_4(sc, IWI_CSR_RST) |
	    IWI_RST_STOP_MASTER);
	for (ntries = 0; ntries < 5; ntries++) {
		if (CSR_READ_4(sc, IWI_CSR_RST) & IWI_RST_MASTER_DISABLED)
			break;
		DELAY(10);
	}
	if (ntries == 5) {
		device_printf(sc->sc_dev, "timeout waiting for master\n");
		error = EIO;
		goto fail;
	}

	MEM_WRITE_4(sc, 0x3000e0, 0x80000000);
	DELAY(5000);

	tmp = CSR_READ_4(sc, IWI_CSR_RST);
	tmp &= ~IWI_RST_PRINCETON_RESET;
	CSR_WRITE_4(sc, IWI_CSR_RST, tmp);

	DELAY(5000);
	MEM_WRITE_4(sc, 0x3000e0, 0);
	DELAY(1000);
	MEM_WRITE_4(sc, IWI_MEM_EEPROM_EVENT, 1);
	DELAY(1000);
	MEM_WRITE_4(sc, IWI_MEM_EEPROM_EVENT, 0);
	DELAY(1000);
	MEM_WRITE_1(sc, 0x200000, 0x00);
	MEM_WRITE_1(sc, 0x200000, 0x40);
	DELAY(1000);

	/* write microcode into adapter memory */
	for (w = (const uint16_t *)uc; size > 0; w++, size -= 2)
		MEM_WRITE_2(sc, 0x200010, htole16(*w));

	MEM_WRITE_1(sc, 0x200000, 0x00);
	MEM_WRITE_1(sc, 0x200000, 0x80);

	/* wait until we get an answer */
	for (ntries = 0; ntries < 100; ntries++) {
		if (MEM_READ_1(sc, 0x200000) & 1)
			break;
		DELAY(100);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev,
		    "timeout waiting for ucode to initialize\n");
		error = EIO;
		goto fail;
	}

	/* read the answer or the firmware will not initialize properly */
	for (i = 0; i < 7; i++)
		MEM_READ_4(sc, 0x200004);

	MEM_WRITE_1(sc, 0x200000, 0x00);

fail:
	return error;
}