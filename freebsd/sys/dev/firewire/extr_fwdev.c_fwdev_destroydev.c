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
struct firewire_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 

int
fwdev_destroydev(struct firewire_softc *sc)
{
	int err = 0;

	destroy_dev(sc->dev);
	return (err);
}