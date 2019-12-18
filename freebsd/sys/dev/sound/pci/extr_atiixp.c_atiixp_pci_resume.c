#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ fmt; int flags; int /*<<< orphan*/ * channel; } ;
struct atiixp_info {scalar_t__ polling; TYPE_1__ rch; TYPE_1__ pch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATI_IXP_CHN_SUSPEND ; 
 int ENXIO ; 
 int /*<<< orphan*/  PCMTRIG_START ; 
 int /*<<< orphan*/  atiixp_chan_setformat (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  atiixp_chan_trigger (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_enable_interrupts (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_lock (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_reset_aclink (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_unlock (struct atiixp_info*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mixer_reinit (int /*<<< orphan*/ ) ; 
 struct atiixp_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atiixp_pci_resume(device_t dev)
{
	struct atiixp_info *sc = pcm_getdevinfo(dev);

	atiixp_lock(sc);
	/* reset / power up aclink */
	atiixp_reset_aclink(sc);
	atiixp_unlock(sc);

	if (mixer_reinit(dev) == -1) {
		device_printf(dev, "unable to reinitialize the mixer\n");
		return (ENXIO);
	}

	/*
	 * Resume channel activities. Reset channel format regardless
	 * of its previous state.
	 */
	if (sc->pch.channel != NULL) {
		if (sc->pch.fmt != 0)
			atiixp_chan_setformat(NULL, &sc->pch, sc->pch.fmt);
		if (sc->pch.flags & ATI_IXP_CHN_SUSPEND) {
			sc->pch.flags &= ~ATI_IXP_CHN_SUSPEND;
			atiixp_chan_trigger(NULL, &sc->pch, PCMTRIG_START);
		}
	}
	if (sc->rch.channel != NULL) {
		if (sc->rch.fmt != 0)
			atiixp_chan_setformat(NULL, &sc->rch, sc->rch.fmt);
		if (sc->rch.flags & ATI_IXP_CHN_SUSPEND) {
			sc->rch.flags &= ~ATI_IXP_CHN_SUSPEND;
			atiixp_chan_trigger(NULL, &sc->rch, PCMTRIG_START);
		}
	}

	/* enable interrupts */
	atiixp_lock(sc);
	if (sc->polling == 0)
		atiixp_enable_interrupts(sc);
	atiixp_unlock(sc);

	return (0);
}