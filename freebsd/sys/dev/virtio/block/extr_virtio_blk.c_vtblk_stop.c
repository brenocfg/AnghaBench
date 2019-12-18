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
struct vtblk_softc {int /*<<< orphan*/  vtblk_dev; int /*<<< orphan*/  vtblk_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_disable_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtblk_stop(struct vtblk_softc *sc)
{

	virtqueue_disable_intr(sc->vtblk_vq);
	virtio_stop(sc->vtblk_dev);
}