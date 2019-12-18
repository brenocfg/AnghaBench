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
struct vtrnd_softc {int /*<<< orphan*/  vtrnd_vq; } ;
struct vq_alloc_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VQ_ALLOC_INFO_INIT (struct vq_alloc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vtrnd_softc*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vtrnd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int virtio_alloc_virtqueues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct vq_alloc_info*) ; 

__attribute__((used)) static int
vtrnd_alloc_virtqueue(device_t dev)
{
	struct vtrnd_softc *sc;
	struct vq_alloc_info vq_info;

	sc = device_get_softc(dev);

	VQ_ALLOC_INFO_INIT(&vq_info, 0, NULL, sc, &sc->vtrnd_vq,
	    "%s request", device_get_nameunit(dev));

	return (virtio_alloc_virtqueues(dev, 0, 1, &vq_info));
}