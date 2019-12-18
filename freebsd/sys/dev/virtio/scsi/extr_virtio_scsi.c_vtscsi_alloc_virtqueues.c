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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_request_vq; int /*<<< orphan*/  vtscsi_max_nsegs; int /*<<< orphan*/  vtscsi_event_vq; int /*<<< orphan*/  vtscsi_control_vq; int /*<<< orphan*/  vtscsi_dev; } ;
struct vq_alloc_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VQ_ALLOC_INFO_INIT (struct vq_alloc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vtscsi_softc*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int virtio_alloc_virtqueues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct vq_alloc_info*) ; 
 int /*<<< orphan*/  vtscsi_control_vq_intr ; 
 int /*<<< orphan*/  vtscsi_event_vq_intr ; 
 int /*<<< orphan*/  vtscsi_request_vq_intr ; 

__attribute__((used)) static int
vtscsi_alloc_virtqueues(struct vtscsi_softc *sc)
{
	device_t dev;
	struct vq_alloc_info vq_info[3];
	int nvqs;

	dev = sc->vtscsi_dev;
	nvqs = 3;

	VQ_ALLOC_INFO_INIT(&vq_info[0], 0, vtscsi_control_vq_intr, sc,
	    &sc->vtscsi_control_vq, "%s control", device_get_nameunit(dev));

	VQ_ALLOC_INFO_INIT(&vq_info[1], 0, vtscsi_event_vq_intr, sc,
	    &sc->vtscsi_event_vq, "%s event", device_get_nameunit(dev));

	VQ_ALLOC_INFO_INIT(&vq_info[2], sc->vtscsi_max_nsegs,
	    vtscsi_request_vq_intr, sc, &sc->vtscsi_request_vq,
	    "%s request", device_get_nameunit(dev));

	return (virtio_alloc_virtqueues(dev, 0, nvqs, vq_info));
}