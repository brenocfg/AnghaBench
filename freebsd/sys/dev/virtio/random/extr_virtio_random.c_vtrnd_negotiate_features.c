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
struct vtrnd_softc {int /*<<< orphan*/  vtrnd_features; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTRND_FEATURES ; 
 struct vtrnd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_negotiate_features (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtrnd_negotiate_features(device_t dev)
{
	struct vtrnd_softc *sc;

	sc = device_get_softc(dev);
	sc->vtrnd_features = virtio_negotiate_features(dev, VTRND_FEATURES);
}