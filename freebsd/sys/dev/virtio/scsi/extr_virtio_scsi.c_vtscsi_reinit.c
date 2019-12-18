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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_features; int /*<<< orphan*/  vtscsi_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 int virtio_reinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_reinit_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vtscsi_enable_vqs_intr (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_reinit_event_vq (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_write_device_config (struct vtscsi_softc*) ; 

__attribute__((used)) static int
vtscsi_reinit(struct vtscsi_softc *sc)
{
	device_t dev;
	int error;

	dev = sc->vtscsi_dev;

	error = virtio_reinit(dev, sc->vtscsi_features);
	if (error == 0) {
		vtscsi_write_device_config(sc);
		vtscsi_reinit_event_vq(sc);
		virtio_reinit_complete(dev);

		vtscsi_enable_vqs_intr(sc);
	}

	vtscsi_dprintf(sc, VTSCSI_TRACE, "error=%d\n", error);

	return (error);
}