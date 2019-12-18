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
typedef  int /*<<< orphan*/  u_char ;
struct iwi_softc {int fw_physaddr; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  fw_map; int /*<<< orphan*/  fw_dmat; int /*<<< orphan*/ * fw_virtaddr; } ;
struct iwi_fw {int size; int /*<<< orphan*/  name; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CSR_READ_4 (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct iwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int GETLE32 (int /*<<< orphan*/ *) ; 
 int IWI_CB_DEFAULT_CTL ; 
 int /*<<< orphan*/  IWI_CB_MAXDATALEN ; 
 int /*<<< orphan*/  IWI_CSR_AUTOINC_ADDR ; 
 int /*<<< orphan*/  IWI_CSR_AUTOINC_DATA ; 
 int /*<<< orphan*/  IWI_CSR_CTL ; 
 int /*<<< orphan*/  IWI_CSR_INTR_MASK ; 
 int /*<<< orphan*/  IWI_CSR_RST ; 
 int IWI_CTL_ALLOW_STANDBY ; 
 int IWI_INTR_MASK ; 
 int /*<<< orphan*/  IWI_LOCK_ASSERT (struct iwi_softc*) ; 
 int IWI_RST_MASTER_DISABLED ; 
 int IWI_RST_STOP_MASTER ; 
 int MEM_READ_4 (struct iwi_softc*,int) ; 
 int /*<<< orphan*/  MEM_WRITE_4 (struct iwi_softc*,int,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int msleep (struct iwi_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwi_load_firmware(struct iwi_softc *sc, const struct iwi_fw *fw)
{
	u_char *p, *end;
	uint32_t sentinel, ctl, src, dst, sum, len, mlen, tmp;
	int ntries, error;

	IWI_LOCK_ASSERT(sc);

	/* copy firmware image to DMA memory */
	memcpy(sc->fw_virtaddr, fw->data, fw->size);

	/* make sure the adapter will get up-to-date values */
	bus_dmamap_sync(sc->fw_dmat, sc->fw_map, BUS_DMASYNC_PREWRITE);

	/* tell the adapter where the command blocks are stored */
	MEM_WRITE_4(sc, 0x3000a0, 0x27000);

	/*
	 * Store command blocks into adapter's internal memory using register
	 * indirections. The adapter will read the firmware image through DMA
	 * using information stored in command blocks.
	 */
	src = sc->fw_physaddr;
	p = sc->fw_virtaddr;
	end = p + fw->size;
	CSR_WRITE_4(sc, IWI_CSR_AUTOINC_ADDR, 0x27000);

	while (p < end) {
		dst = GETLE32(p); p += 4; src += 4;
		len = GETLE32(p); p += 4; src += 4;
		p += len;

		while (len > 0) {
			mlen = min(len, IWI_CB_MAXDATALEN);

			ctl = IWI_CB_DEFAULT_CTL | mlen;
			sum = ctl ^ src ^ dst;

			/* write a command block */
			CSR_WRITE_4(sc, IWI_CSR_AUTOINC_DATA, ctl);
			CSR_WRITE_4(sc, IWI_CSR_AUTOINC_DATA, src);
			CSR_WRITE_4(sc, IWI_CSR_AUTOINC_DATA, dst);
			CSR_WRITE_4(sc, IWI_CSR_AUTOINC_DATA, sum);

			src += mlen;
			dst += mlen;
			len -= mlen;
		}
	}

	/* write a fictive final command block (sentinel) */
	sentinel = CSR_READ_4(sc, IWI_CSR_AUTOINC_ADDR);
	CSR_WRITE_4(sc, IWI_CSR_AUTOINC_DATA, 0);

	tmp = CSR_READ_4(sc, IWI_CSR_RST);
	tmp &= ~(IWI_RST_MASTER_DISABLED | IWI_RST_STOP_MASTER);
	CSR_WRITE_4(sc, IWI_CSR_RST, tmp);

	/* tell the adapter to start processing command blocks */
	MEM_WRITE_4(sc, 0x3000a4, 0x540100);

	/* wait until the adapter reaches the sentinel */
	for (ntries = 0; ntries < 400; ntries++) {
		if (MEM_READ_4(sc, 0x3000d0) >= sentinel)
			break;
		DELAY(100);
	}
	/* sync dma, just in case */
	bus_dmamap_sync(sc->fw_dmat, sc->fw_map, BUS_DMASYNC_POSTWRITE);
	if (ntries == 400) {
		device_printf(sc->sc_dev,
		    "timeout processing command blocks for %s firmware\n",
		    fw->name);
		return EIO;
	}

	/* we're done with command blocks processing */
	MEM_WRITE_4(sc, 0x3000a4, 0x540c00);

	/* allow interrupts so we know when the firmware is ready */
	CSR_WRITE_4(sc, IWI_CSR_INTR_MASK, IWI_INTR_MASK);

	/* tell the adapter to initialize the firmware */
	CSR_WRITE_4(sc, IWI_CSR_RST, 0);

	tmp = CSR_READ_4(sc, IWI_CSR_CTL);
	CSR_WRITE_4(sc, IWI_CSR_CTL, tmp | IWI_CTL_ALLOW_STANDBY);

	/* wait at most one second for firmware initialization to complete */
	if ((error = msleep(sc, &sc->sc_mtx, 0, "iwiinit", hz)) != 0) {
		device_printf(sc->sc_dev, "timeout waiting for %s firmware "
		    "initialization to complete\n", fw->name);
	}

	return error;
}