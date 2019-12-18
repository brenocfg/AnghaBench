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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_features; int /*<<< orphan*/  vtscsi_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_FEATURES ; 
 int /*<<< orphan*/  virtio_negotiate_features (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtscsi_negotiate_features(struct vtscsi_softc *sc)
{
	device_t dev;
	uint64_t features;

	dev = sc->vtscsi_dev;
	features = virtio_negotiate_features(dev, VTSCSI_FEATURES);
	sc->vtscsi_features = features;
}