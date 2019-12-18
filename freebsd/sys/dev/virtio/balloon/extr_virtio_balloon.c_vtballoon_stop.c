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
struct vtballoon_softc {int /*<<< orphan*/  vtballoon_dev; int /*<<< orphan*/  vtballoon_deflate_vq; int /*<<< orphan*/  vtballoon_inflate_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_disable_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtballoon_stop(struct vtballoon_softc *sc)
{

	virtqueue_disable_intr(sc->vtballoon_inflate_vq);
	virtqueue_disable_intr(sc->vtballoon_deflate_vq);

	virtio_stop(sc->vtballoon_dev);
}