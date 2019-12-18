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
struct vtballoon_softc {int /*<<< orphan*/  vtballoon_deflate_vq; int /*<<< orphan*/  vtballoon_inflate_vq; int /*<<< orphan*/  vtballoon_dev; } ;
struct vq_alloc_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VQ_ALLOC_INFO_INIT (struct vq_alloc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vtballoon_softc*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int virtio_alloc_virtqueues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct vq_alloc_info*) ; 
 int /*<<< orphan*/  vtballoon_vq_intr ; 

__attribute__((used)) static int
vtballoon_alloc_virtqueues(struct vtballoon_softc *sc)
{
	device_t dev;
	struct vq_alloc_info vq_info[2];
	int nvqs;

	dev = sc->vtballoon_dev;
	nvqs = 2;

	VQ_ALLOC_INFO_INIT(&vq_info[0], 0, vtballoon_vq_intr, sc,
	    &sc->vtballoon_inflate_vq, "%s inflate", device_get_nameunit(dev));

	VQ_ALLOC_INFO_INIT(&vq_info[1], 0, vtballoon_vq_intr, sc,
	    &sc->vtballoon_deflate_vq, "%s deflate", device_get_nameunit(dev));

	return (virtio_alloc_virtqueues(dev, 0, nvqs, vq_info));
}