#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct sc_info {int nchans; int /*<<< orphan*/  lock; TYPE_2__* rch; TYPE_1__* pch; int /*<<< orphan*/  dev; int /*<<< orphan*/  mpu; int /*<<< orphan*/  (* mpu_intr ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ channel; } ;
struct TYPE_3__ {scalar_t__ channel; scalar_t__ run; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_IPR ; 
 int EMU_IPR_ADCBUFFULL ; 
 int EMU_IPR_ADCBUFHALFFULL ; 
 int EMU_IPR_EFXBUFFULL ; 
 int EMU_IPR_EFXBUFHALFFULL ; 
 int EMU_IPR_INTERVALTIMER ; 
 int EMU_IPR_MICBUFFULL ; 
 int EMU_IPR_MICBUFHALFFULL ; 
 int EMU_IPR_MIDIRECVBUFE ; 
 int EMU_IPR_MIDITRANSBUFE ; 
 int EMU_IPR_RATETRCHANGE ; 
 int EMU_PCIERROR ; 
 int /*<<< orphan*/  chn_intr (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  emu_enatimer (struct sc_info*,int /*<<< orphan*/ ) ; 
 int emu_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emu_intr(void *data)
{
	struct sc_info *sc = data;
	u_int32_t stat, ack, i, x;

	snd_mtxlock(sc->lock);
	while (1) {
		stat = emu_rd(sc, EMU_IPR, 4);
		if (stat == 0)
			break;
		ack = 0;

		/* process irq */
		if (stat & EMU_IPR_INTERVALTIMER)
			ack |= EMU_IPR_INTERVALTIMER;

		if (stat & (EMU_IPR_ADCBUFFULL | EMU_IPR_ADCBUFHALFFULL))
			ack |= stat & (EMU_IPR_ADCBUFFULL | EMU_IPR_ADCBUFHALFFULL);

		if (stat & (EMU_IPR_EFXBUFFULL | EMU_IPR_EFXBUFHALFFULL))
			ack |= stat & (EMU_IPR_EFXBUFFULL | EMU_IPR_EFXBUFHALFFULL);

		if (stat & (EMU_IPR_MICBUFFULL | EMU_IPR_MICBUFHALFFULL))
			ack |= stat & (EMU_IPR_MICBUFFULL | EMU_IPR_MICBUFHALFFULL);

		if (stat & EMU_PCIERROR) {
			ack |= EMU_PCIERROR;
			device_printf(sc->dev, "pci error\n");
			/* we still get an nmi with ecc ram even if we ack this */
		}
		if (stat & EMU_IPR_RATETRCHANGE) {
			ack |= EMU_IPR_RATETRCHANGE;
#ifdef EMUDEBUG
			device_printf(sc->dev,
			    "sample rate tracker lock status change\n");
#endif
		}

	    if (stat & EMU_IPR_MIDIRECVBUFE)
		if (sc->mpu_intr) {
		    (sc->mpu_intr)(sc->mpu);
		    ack |= EMU_IPR_MIDIRECVBUFE | EMU_IPR_MIDITRANSBUFE;
 		}
		if (stat & ~ack)
			device_printf(sc->dev, "dodgy irq: %x (harmless)\n",
			    stat & ~ack);

		emu_wr(sc, EMU_IPR, stat, 4);

		if (ack) {
			snd_mtxunlock(sc->lock);

			if (ack & EMU_IPR_INTERVALTIMER) {
				x = 0;
				for (i = 0; i < sc->nchans; i++) {
					if (sc->pch[i].run) {
						x = 1;
						chn_intr(sc->pch[i].channel);
					}
				}
				if (x == 0)
					emu_enatimer(sc, 0);
			}


			if (ack & (EMU_IPR_ADCBUFFULL | EMU_IPR_ADCBUFHALFFULL)) {
				if (sc->rch[0].channel)
					chn_intr(sc->rch[0].channel);
			}
			if (ack & (EMU_IPR_EFXBUFFULL | EMU_IPR_EFXBUFHALFFULL)) {
				if (sc->rch[1].channel)
					chn_intr(sc->rch[1].channel);
			}
			if (ack & (EMU_IPR_MICBUFFULL | EMU_IPR_MICBUFHALFFULL)) {
				if (sc->rch[2].channel)
					chn_intr(sc->rch[2].channel);
			}

			snd_mtxlock(sc->lock);
		}
	}
	snd_mtxunlock(sc->lock);
}