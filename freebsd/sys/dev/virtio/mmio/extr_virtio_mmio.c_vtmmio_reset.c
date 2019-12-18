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
struct vtmmio_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_RESET ; 
 int /*<<< orphan*/  vtmmio_set_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtmmio_reset(struct vtmmio_softc *sc)
{

	/*
	 * Setting the status to RESET sets the host device to
	 * the original, uninitialized state.
	 */
	vtmmio_set_status(sc->dev, VIRTIO_CONFIG_STATUS_RESET);
}