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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ntb_plx_softc {size_t b2b_mw; int mw_count; scalar_t__ link; scalar_t__ alut; struct ntb_plx_mw_info* mw_info; } ;
struct ntb_plx_mw_info {int mw_bar; scalar_t__ mw_64bit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int NTX_READ (struct ntb_plx_softc*,int) ; 
 int /*<<< orphan*/  NTX_WRITE (struct ntb_plx_softc*,int,int) ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_MEMEN ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int PCIR_COMMAND ; 
 int /*<<< orphan*/  PNTX_WRITE (struct ntb_plx_softc*,int,int) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_plx_mw_set_trans_internal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ntb_plx_init(device_t dev)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);
	struct ntb_plx_mw_info *mw;
	uint64_t val64;
	int i;
	uint32_t val;

	if (sc->b2b_mw >= 0) {
		/* Set peer BAR0/1 size and address for B2B NTx access. */
		mw = &sc->mw_info[sc->b2b_mw];
		if (mw->mw_64bit) {
			PNTX_WRITE(sc, 0xe4, 0x3);	/* 64-bit */
			val64 = 0x2000000000000000 * mw->mw_bar | 0x4;
			PNTX_WRITE(sc, PCIR_BAR(0), val64);
			PNTX_WRITE(sc, PCIR_BAR(0) + 4, val64 >> 32);
		} else {
			PNTX_WRITE(sc, 0xe4, 0x2);	/* 32-bit */
			val = 0x20000000 * mw->mw_bar;
			PNTX_WRITE(sc, PCIR_BAR(0), val);
		}

		/* Set Virtual to Link address translation for B2B. */
		for (i = 0; i < sc->mw_count; i++) {
			mw = &sc->mw_info[i];
			if (mw->mw_64bit) {
				val64 = 0x2000000000000000 * mw->mw_bar;
				NTX_WRITE(sc, 0xc3c + (mw->mw_bar - 2) * 4, val64);
				NTX_WRITE(sc, 0xc3c + (mw->mw_bar - 2) * 4 + 4, val64 >> 32);
			} else {
				val = 0x20000000 * mw->mw_bar;
				NTX_WRITE(sc, 0xc3c + (mw->mw_bar - 2) * 4, val);
			}
		}

		/* Make sure Virtual to Link A-LUT is disabled. */
		if (sc->alut)
			PNTX_WRITE(sc, 0xc94, 0);

		/* Enable all Link Interface LUT entries for peer. */
		for (i = 0; i < 32; i += 2) {
			PNTX_WRITE(sc, 0xdb4 + i * 2,
			    0x00010001 | ((i + 1) << 19) | (i << 3));
		}
	}

	/*
	 * Enable Virtual Interface LUT entry 0 for 0:0.*.
	 * entry 1 for our Requester ID reported by the chip,
	 * entries 2-5 for 0/64/128/192:4.* of I/OAT DMA engines.
	 * XXX: Its a hack, we can't know all DMA engines, but this covers all
	 * I/OAT of Xeon E5/E7 at least from Sandy Bridge till Skylake I saw.
	 */
	val = (NTX_READ(sc, 0xc90) << 16) | 0x00010001;
	NTX_WRITE(sc, sc->link ? 0xdb4 : 0xd94, val);
	NTX_WRITE(sc, sc->link ? 0xdb8 : 0xd98, 0x40210021);
	NTX_WRITE(sc, sc->link ? 0xdbc : 0xd9c, 0xc0218021);

	/* Set Link to Virtual address translation. */
	for (i = 0; i < sc->mw_count; i++)
		ntb_plx_mw_set_trans_internal(dev, i);

	pci_enable_busmaster(dev);
	if (sc->b2b_mw >= 0)
		PNTX_WRITE(sc, PCIR_COMMAND, PCIM_CMD_MEMEN | PCIM_CMD_BUSMASTEREN);

	return (0);
}