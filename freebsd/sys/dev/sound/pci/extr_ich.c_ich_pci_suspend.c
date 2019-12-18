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
struct sc_info {TYPE_1__* ch; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ run; scalar_t__ run_save; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICH_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  ICH_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  PCMTRIG_ABORT ; 
 int /*<<< orphan*/  ichchan_trigger (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ich_pci_suspend(device_t dev)
{
	struct sc_info *sc;
	int i;

	sc = pcm_getdevinfo(dev);
	ICH_LOCK(sc);
	for (i = 0 ; i < 3; i++) {
		sc->ch[i].run_save = sc->ch[i].run;
		if (sc->ch[i].run) {
			ICH_UNLOCK(sc);
			ichchan_trigger(0, &sc->ch[i], PCMTRIG_ABORT);
			ICH_LOCK(sc);
		}
	}
	ICH_UNLOCK(sc);
	return (0);
}