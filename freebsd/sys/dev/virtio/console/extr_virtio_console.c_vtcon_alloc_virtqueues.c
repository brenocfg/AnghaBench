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
struct vtcon_softc_port {int /*<<< orphan*/  vcsp_outvq; int /*<<< orphan*/  vcsp_invq; } ;
struct vtcon_softc {int vtcon_max_ports; int vtcon_flags; struct vtcon_softc_port* vtcon_ports; int /*<<< orphan*/  vtcon_ctrl_txvq; int /*<<< orphan*/  vtcon_ctrl_rxvq; int /*<<< orphan*/  vtcon_dev; } ;
struct vq_alloc_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  VQ_ALLOC_INFO_INIT (struct vq_alloc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int VTCON_FLAG_MULTIPORT ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vq_alloc_info*,int /*<<< orphan*/ ) ; 
 struct vq_alloc_info* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtio_alloc_virtqueues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct vq_alloc_info*) ; 
 int /*<<< orphan*/  vtcon_ctrl_event_intr ; 
 int /*<<< orphan*/ * vtcon_port_intr ; 

__attribute__((used)) static int
vtcon_alloc_virtqueues(struct vtcon_softc *sc)
{
	device_t dev;
	struct vq_alloc_info *info;
	struct vtcon_softc_port *scport;
	int i, idx, portidx, nvqs, error;

	dev = sc->vtcon_dev;

	nvqs = sc->vtcon_max_ports * 2;
	if (sc->vtcon_flags & VTCON_FLAG_MULTIPORT)
		nvqs += 2;

	info = malloc(sizeof(struct vq_alloc_info) * nvqs, M_TEMP, M_NOWAIT);
	if (info == NULL)
		return (ENOMEM);

	for (i = 0, idx = 0, portidx = 0; i < nvqs / 2; i++, idx += 2) {

		if (i == 1) {
			/* The control virtqueues are after the first port. */
			VQ_ALLOC_INFO_INIT(&info[idx], 0,
			    vtcon_ctrl_event_intr, sc, &sc->vtcon_ctrl_rxvq,
			    "%s-control rx", device_get_nameunit(dev));
			VQ_ALLOC_INFO_INIT(&info[idx+1], 0,
			    NULL, sc, &sc->vtcon_ctrl_txvq,
			    "%s-control tx", device_get_nameunit(dev));
			continue;
		}

		scport = &sc->vtcon_ports[portidx];

		VQ_ALLOC_INFO_INIT(&info[idx], 0, vtcon_port_intr,
		    scport, &scport->vcsp_invq, "%s-port%d in",
		    device_get_nameunit(dev), i);
		VQ_ALLOC_INFO_INIT(&info[idx+1], 0, NULL,
		    NULL, &scport->vcsp_outvq, "%s-port%d out",
		    device_get_nameunit(dev), i);

		portidx++;
	}

	error = virtio_alloc_virtqueues(dev, 0, nvqs, info);
	free(info, M_TEMP);

	return (error);
}