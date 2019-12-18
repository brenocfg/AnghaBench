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
struct ip17x_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IP17X_LOCK (struct ip17x_softc*) ; 
 int /*<<< orphan*/  IP17X_LOCK_ASSERT (struct ip17x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 struct ip17x_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ip17x_lock(device_t dev)
{
	struct ip17x_softc *sc;

	sc = device_get_softc(dev);
	IP17X_LOCK_ASSERT(sc, MA_NOTOWNED);
	IP17X_LOCK(sc);
}