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
struct mfip_softc {int /*<<< orphan*/ * devq; int /*<<< orphan*/ * sim; struct mfi_softc* mfi_sc; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_cam_rescan_cb; int /*<<< orphan*/  mfi_cam_start; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MFIP_STATE_NONE ; 
 int /*<<< orphan*/  MFI_SCSI_MAX_CMDS ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mfip_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mfip_cam_action ; 
 int /*<<< orphan*/  mfip_cam_poll ; 
 int /*<<< orphan*/  mfip_cam_rescan ; 
 int /*<<< orphan*/  mfip_start ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mfip_attach(device_t dev)
{
	struct mfip_softc *sc;
	struct mfi_softc *mfisc;

	sc = device_get_softc(dev);
	if (sc == NULL)
		return (EINVAL);

	mfisc = device_get_softc(device_get_parent(dev));
	sc->dev = dev;
	sc->state = MFIP_STATE_NONE;
	sc->mfi_sc = mfisc;
	mfisc->mfi_cam_start = mfip_start;

	if ((sc->devq = cam_simq_alloc(MFI_SCSI_MAX_CMDS)) == NULL)
		return (ENOMEM);

	sc->sim = cam_sim_alloc(mfip_cam_action, mfip_cam_poll, "mfi", sc,
				device_get_unit(dev), &mfisc->mfi_io_lock, 1,
				MFI_SCSI_MAX_CMDS, sc->devq);
	if (sc->sim == NULL) {
		cam_simq_free(sc->devq);
		sc->devq = NULL;
		device_printf(dev, "CAM SIM attach failed\n");
		return (EINVAL);
	}

	mfisc->mfi_cam_rescan_cb = mfip_cam_rescan;

	mtx_lock(&mfisc->mfi_io_lock);
	if (xpt_bus_register(sc->sim, dev, 0) != 0) {
		device_printf(dev, "XPT bus registration failed\n");
		cam_sim_free(sc->sim, FALSE);
		sc->sim = NULL;
		cam_simq_free(sc->devq);
		sc->devq = NULL;
		mtx_unlock(&mfisc->mfi_io_lock);
		return (EINVAL);
	}
	mtx_unlock(&mfisc->mfi_io_lock);

	return (0);
}