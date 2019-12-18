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
typedef  int /*<<< orphan*/  target_id_t ;
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_dev; } ;
struct virtio_scsi_event {int reason; int /*<<< orphan*/  lun; } ;
typedef  int /*<<< orphan*/  lun_id_t ;

/* Variables and functions */
#define  VIRTIO_SCSI_EVT_RESET_REMOVED 129 
#define  VIRTIO_SCSI_EVT_RESET_RESCAN 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vtscsi_execute_rescan (struct vtscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_get_request_lun (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtscsi_transport_reset_event(struct vtscsi_softc *sc,
    struct virtio_scsi_event *event)
{
	target_id_t target_id;
	lun_id_t lun_id;

	vtscsi_get_request_lun(event->lun, &target_id, &lun_id);

	switch (event->reason) {
	case VIRTIO_SCSI_EVT_RESET_RESCAN:
	case VIRTIO_SCSI_EVT_RESET_REMOVED:
		vtscsi_execute_rescan(sc, target_id, lun_id);
		break;
	default:
		device_printf(sc->vtscsi_dev,
		    "unhandled transport event reason: %d\n", event->reason);
		break;
	}
}