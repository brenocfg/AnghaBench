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
struct vtmmio_softc {int /*<<< orphan*/  vtmmio_child_feat_desc; int /*<<< orphan*/  vtmmio_child_dev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_describe (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtmmio_describe_features(struct vtmmio_softc *sc, const char *msg,
    uint64_t features)
{
	device_t dev, child;

	dev = sc->dev;
	child = sc->vtmmio_child_dev;

	if (device_is_attached(child) || bootverbose == 0)
		return;

	virtio_describe(dev, msg, features, sc->vtmmio_child_feat_desc);
}