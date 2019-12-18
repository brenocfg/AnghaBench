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
typedef  int /*<<< orphan*/  uint64_t ;
struct vtballoon_softc {int /*<<< orphan*/  vtballoon_features; int /*<<< orphan*/  vtballoon_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTBALLOON_FEATURES ; 
 int /*<<< orphan*/  virtio_negotiate_features (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtballoon_negotiate_features(struct vtballoon_softc *sc)
{
	device_t dev;
	uint64_t features;

	dev = sc->vtballoon_dev;
	features = virtio_negotiate_features(dev, VTBALLOON_FEATURES);
	sc->vtballoon_features = features;
}