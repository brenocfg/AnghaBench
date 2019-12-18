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
struct vtblk_softc {int /*<<< orphan*/  vtblk_flags; int /*<<< orphan*/  vtblk_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_BLK_F_BARRIER ; 
 int /*<<< orphan*/  VIRTIO_BLK_F_CONFIG_WCE ; 
 int /*<<< orphan*/  VIRTIO_BLK_F_RO ; 
 int /*<<< orphan*/  VIRTIO_RING_F_INDIRECT_DESC ; 
 int /*<<< orphan*/  VTBLK_FLAG_BARRIER ; 
 int /*<<< orphan*/  VTBLK_FLAG_INDIRECT ; 
 int /*<<< orphan*/  VTBLK_FLAG_READONLY ; 
 int /*<<< orphan*/  VTBLK_FLAG_WC_CONFIG ; 
 scalar_t__ virtio_with_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_negotiate_features (struct vtblk_softc*) ; 

__attribute__((used)) static void
vtblk_setup_features(struct vtblk_softc *sc)
{
	device_t dev;

	dev = sc->vtblk_dev;

	vtblk_negotiate_features(sc);

	if (virtio_with_feature(dev, VIRTIO_RING_F_INDIRECT_DESC))
		sc->vtblk_flags |= VTBLK_FLAG_INDIRECT;
	if (virtio_with_feature(dev, VIRTIO_BLK_F_RO))
		sc->vtblk_flags |= VTBLK_FLAG_READONLY;
	if (virtio_with_feature(dev, VIRTIO_BLK_F_BARRIER))
		sc->vtblk_flags |= VTBLK_FLAG_BARRIER;
	if (virtio_with_feature(dev, VIRTIO_BLK_F_CONFIG_WCE))
		sc->vtblk_flags |= VTBLK_FLAG_WC_CONFIG;
}