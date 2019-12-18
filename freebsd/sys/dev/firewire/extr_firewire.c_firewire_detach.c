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
struct fw_device {int dummy; } ;
struct firewire_softc {struct firewire_comm* fc; } ;
struct firewire_comm {int /*<<< orphan*/  wait_lock; int /*<<< orphan*/  tlabel_lock; struct fw_device* crom_src_buf; struct fw_device* speed_map; struct fw_device* topology_map; int /*<<< orphan*/  devices; int /*<<< orphan*/  busprobe_callout; int /*<<< orphan*/  bmr_callout; int /*<<< orphan*/  timeout_callout; TYPE_1__* arq; int /*<<< orphan*/  probe_thread; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ maxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWBUSDETACH ; 
 int /*<<< orphan*/  M_FW ; 
 int /*<<< orphan*/  PWAIT ; 
 struct fw_device* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct fw_device* STAILQ_NEXT (struct fw_device*,int /*<<< orphan*/ ) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct firewire_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_drain_txq (struct firewire_comm*) ; 
 int fwdev_destroydev (struct firewire_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  wakeup (struct firewire_comm*) ; 

__attribute__((used)) static int
firewire_detach(device_t dev)
{
	struct firewire_softc *sc;
	struct firewire_comm *fc;
	struct fw_device *fwdev, *fwdev_next;
	int err;

	sc = device_get_softc(dev);
	fc = sc->fc;
	mtx_lock(&fc->wait_lock);
	fc->status = FWBUSDETACH;
	wakeup(fc);
	if (msleep(fc->probe_thread, &fc->wait_lock, PWAIT, "fwthr", hz * 60))
		printf("firewire probe thread didn't die\n");
	mtx_unlock(&fc->wait_lock);

	if (fc->arq != 0 && fc->arq->maxq > 0)
		fw_drain_txq(fc);

	if ((err = fwdev_destroydev(sc)) != 0)
		return err;

	if ((err = bus_generic_detach(dev)) != 0)
		return err;

	callout_stop(&fc->timeout_callout);
	callout_stop(&fc->bmr_callout);
	callout_stop(&fc->busprobe_callout);

	/* XXX xfer_free and untimeout on all xfers */
	for (fwdev = STAILQ_FIRST(&fc->devices); fwdev != NULL;
	     fwdev = fwdev_next) {
		fwdev_next = STAILQ_NEXT(fwdev, link);
		free(fwdev, M_FW);
	}
	free(fc->topology_map, M_FW);
	free(fc->speed_map, M_FW);
	free(fc->crom_src_buf, M_FW);

	mtx_destroy(&fc->tlabel_lock);
	mtx_destroy(&fc->wait_lock);
	return (0);
}