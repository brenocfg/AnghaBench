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
typedef  int /*<<< orphan*/  uint32_t ;
struct sndcard_func {scalar_t__ varinfo; } ;
struct emu_midiinfo {scalar_t__ port; int /*<<< orphan*/  card; } ;
struct emu_midi_softc {scalar_t__ port; int /*<<< orphan*/  card; scalar_t__ is_emu10k1; int /*<<< orphan*/  mtx; int /*<<< orphan*/  ihandle; int /*<<< orphan*/ * mpu; int /*<<< orphan*/  mpu_intr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ EMU_A_MUDATA1 ; 
 int /*<<< orphan*/  EMU_INTE_A_MIDIRXENABLE2 ; 
 int /*<<< orphan*/  EMU_INTE_MIDIRXENABLE ; 
 int /*<<< orphan*/  EMU_IPR_A_MIDIRECBUFE2 ; 
 int /*<<< orphan*/  EMU_IPR_A_MIDITRANSBUFE2 ; 
 int /*<<< orphan*/  EMU_IPR_MIDIRECVBUFE ; 
 int /*<<< orphan*/  EMU_IPR_MIDITRANSBUFE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 struct sndcard_func* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct emu_midi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_enable_ir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_intr_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct emu_midi_softc*) ; 
 int /*<<< orphan*/  emu_intr_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_midi_card_intr ; 
 int /*<<< orphan*/  emu_midi_intr ; 
 int /*<<< orphan*/  emu_mpu_class ; 
 int /*<<< orphan*/ * mpu401_init (int /*<<< orphan*/ *,struct emu_midi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_midi_attach(device_t dev)
{
	struct emu_midi_softc * scp;
	struct sndcard_func *func;
	struct emu_midiinfo *midiinfo;
	uint32_t inte_val, ipr_val;

	scp = device_get_softc(dev);
	func = device_get_ivars(dev);

	scp->dev = dev;
	midiinfo = (struct emu_midiinfo *)func->varinfo;
	scp->port = midiinfo->port;
	scp->card = midiinfo->card;

	mtx_init(&scp->mtx, device_get_nameunit(dev), "midi softc", MTX_DEF);

	if (scp->is_emu10k1) {
		/* SB Live! - only one MIDI device here */
		inte_val = 0;
		/* inte_val |= EMU_INTE_MIDITXENABLE;*/
		inte_val |= EMU_INTE_MIDIRXENABLE;
		ipr_val = EMU_IPR_MIDITRANSBUFE;
		ipr_val |= EMU_IPR_MIDIRECVBUFE;
	} else {
		if (scp->port == EMU_A_MUDATA1) {
			/* EXTERNAL MIDI (AudigyDrive) */
			inte_val = 0;
			/* inte_val |= A_EMU_INTE_MIDITXENABLE1;*/
			inte_val |= EMU_INTE_MIDIRXENABLE;
			ipr_val = EMU_IPR_MIDITRANSBUFE;
			ipr_val |= EMU_IPR_MIDIRECVBUFE;
		} else {
			/* MIDI hw config port 2 */
			inte_val = 0;
			/* inte_val |= A_EMU_INTE_MIDITXENABLE2;*/
			inte_val |= EMU_INTE_A_MIDIRXENABLE2;
			ipr_val = EMU_IPR_A_MIDITRANSBUFE2;
			ipr_val |= EMU_IPR_A_MIDIRECBUFE2;
		}
	}

	scp->ihandle = emu_intr_register(scp->card, inte_val, ipr_val, &emu_midi_card_intr, scp);
	/* Init the interface. */
	scp->mpu = mpu401_init(&emu_mpu_class, scp, emu_midi_intr, &scp->mpu_intr);
	if (scp->mpu == NULL) {
		emu_intr_unregister(scp->card, scp->ihandle);
		mtx_destroy(&scp->mtx);
		return (ENOMEM);
	}
	/*
	 * XXX I don't know how to check for Live!Drive / AudigyDrive
	 * presence. Let's hope that IR enabling code will not harm if
	 * it is not present.
	 */
	if (scp->is_emu10k1)
		emu_enable_ir(scp->card);
	else {
		if (scp->port == EMU_A_MUDATA1)
			emu_enable_ir(scp->card);
	}

	return (0);
}