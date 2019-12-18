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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_disable_vqs_intr (struct vtscsi_softc*) ; 

__attribute__((used)) static void
vtscsi_stop(struct vtscsi_softc *sc)
{

	vtscsi_disable_vqs_intr(sc);
	virtio_stop(sc->vtscsi_dev);
}