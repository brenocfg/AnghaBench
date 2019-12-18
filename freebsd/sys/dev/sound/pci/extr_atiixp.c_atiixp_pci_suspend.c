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
typedef  int uint32_t ;
struct TYPE_2__ {int flags; } ;
struct atiixp_info {TYPE_1__ rch; TYPE_1__ pch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATI_IXP_CHN_RUNNING ; 
 int ATI_IXP_CHN_SUSPEND ; 
 int /*<<< orphan*/  ATI_REG_CMD ; 
 int ATI_REG_CMD_AC_RESET ; 
 int ATI_REG_CMD_POWERDOWN ; 
 int /*<<< orphan*/  PCMTRIG_STOP ; 
 int /*<<< orphan*/  atiixp_chan_trigger (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_disable_interrupts (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_lock (struct atiixp_info*) ; 
 int atiixp_rd (struct atiixp_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_unlock (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_wr (struct atiixp_info*,int /*<<< orphan*/ ,int) ; 
 struct atiixp_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atiixp_pci_suspend(device_t dev)
{
	struct atiixp_info *sc = pcm_getdevinfo(dev);
	uint32_t value;

	/* quickly disable interrupts and save channels active state */
	atiixp_lock(sc);
	atiixp_disable_interrupts(sc);
	atiixp_unlock(sc);

	/* stop everything */
	if (sc->pch.flags & ATI_IXP_CHN_RUNNING) {
		atiixp_chan_trigger(NULL, &sc->pch, PCMTRIG_STOP);
		sc->pch.flags |= ATI_IXP_CHN_SUSPEND;
	}
	if (sc->rch.flags & ATI_IXP_CHN_RUNNING) {
		atiixp_chan_trigger(NULL, &sc->rch, PCMTRIG_STOP);
		sc->rch.flags |= ATI_IXP_CHN_SUSPEND;
	}

	/* power down aclink and pci bus */
	atiixp_lock(sc);
	value = atiixp_rd(sc, ATI_REG_CMD);
	value |= ATI_REG_CMD_POWERDOWN | ATI_REG_CMD_AC_RESET;
	atiixp_wr(sc, ATI_REG_CMD, ATI_REG_CMD_POWERDOWN);
	atiixp_unlock(sc);

	return (0);
}