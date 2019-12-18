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
struct are_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_LOCK (struct are_softc*) ; 
 int /*<<< orphan*/  ARE_UNLOCK (struct are_softc*) ; 
 int /*<<< orphan*/  are_stop (struct are_softc*) ; 
 struct are_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
are_shutdown(device_t dev)
{
	struct are_softc	*sc;

	sc = device_get_softc(dev);

	ARE_LOCK(sc);
	are_stop(sc);
	ARE_UNLOCK(sc);

	return (0);
}