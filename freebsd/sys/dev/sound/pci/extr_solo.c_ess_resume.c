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
typedef  int uint16_t ;
struct ess_info {int /*<<< orphan*/  io; scalar_t__ newspeed; int /*<<< orphan*/  vc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ESS_PCI_CONFIG ; 
 int /*<<< orphan*/  ESS_PCI_DDMACONTROL ; 
 int /*<<< orphan*/  ESS_PCI_LEGACYCONTROL ; 
 int /*<<< orphan*/  ess_lock (struct ess_info*) ; 
 scalar_t__ ess_reset_dsp (struct ess_info*) ; 
 int /*<<< orphan*/  ess_setmixer (struct ess_info*,int,int) ; 
 int /*<<< orphan*/  ess_unlock (struct ess_info*) ; 
 scalar_t__ mixer_reinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct ess_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ ,int,int,int) ; 
 int rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
ess_resume(device_t dev)
{
	uint16_t ddma;
	struct ess_info *sc = pcm_getdevinfo(dev);
	
	ess_lock(sc);
	ddma = rman_get_start(sc->vc) | 1;
	pci_write_config(dev, ESS_PCI_LEGACYCONTROL, 0x805f, 2);
	pci_write_config(dev, ESS_PCI_DDMACONTROL, ddma, 2);
	pci_write_config(dev, ESS_PCI_CONFIG, 0, 2);

    	if (ess_reset_dsp(sc)) {
		ess_unlock(sc);
		goto no;
	}
	ess_unlock(sc);
    	if (mixer_reinit(dev))
		goto no;
	ess_lock(sc);
	if (sc->newspeed)
		ess_setmixer(sc, 0x71, 0x2a);

	port_wr(sc->io, 0x7, 0xb0, 1); /* enable irqs */
	ess_unlock(sc);

	return 0;
 no:
	return EIO;
}