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
struct vtcon_softc {int /*<<< orphan*/  vtcon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtcon_disable_interrupts (struct vtcon_softc*) ; 

__attribute__((used)) static void
vtcon_stop(struct vtcon_softc *sc)
{

	vtcon_disable_interrupts(sc);
	virtio_stop(sc->vtcon_dev);
}