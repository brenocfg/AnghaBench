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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_dev; } ;
struct virtio_scsi_config {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_GET_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_scsi_config*) ; 
 int /*<<< orphan*/  bzero (struct virtio_scsi_config*,int) ; 
 int /*<<< orphan*/  cdb_size ; 
 int /*<<< orphan*/  cmd_per_lun ; 
 int /*<<< orphan*/  event_info_size ; 
 int /*<<< orphan*/  max_channel ; 
 int /*<<< orphan*/  max_lun ; 
 int /*<<< orphan*/  max_sectors ; 
 int /*<<< orphan*/  max_target ; 
 int /*<<< orphan*/  num_queues ; 
 int /*<<< orphan*/  seg_max ; 
 int /*<<< orphan*/  sense_size ; 

__attribute__((used)) static void
vtscsi_read_config(struct vtscsi_softc *sc,
    struct virtio_scsi_config *scsicfg)
{
	device_t dev;

	dev = sc->vtscsi_dev;

	bzero(scsicfg, sizeof(struct virtio_scsi_config));

	VTSCSI_GET_CONFIG(dev, num_queues, scsicfg);
	VTSCSI_GET_CONFIG(dev, seg_max, scsicfg);
	VTSCSI_GET_CONFIG(dev, max_sectors, scsicfg);
	VTSCSI_GET_CONFIG(dev, cmd_per_lun, scsicfg);
	VTSCSI_GET_CONFIG(dev, event_info_size, scsicfg);
	VTSCSI_GET_CONFIG(dev, sense_size, scsicfg);
	VTSCSI_GET_CONFIG(dev, cdb_size, scsicfg);
	VTSCSI_GET_CONFIG(dev, max_channel, scsicfg);
	VTSCSI_GET_CONFIG(dev, max_target, scsicfg);
	VTSCSI_GET_CONFIG(dev, max_lun, scsicfg);
}