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
struct my_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MY_LOCK (struct my_softc*) ; 
 int /*<<< orphan*/  MY_UNLOCK (struct my_softc*) ; 
 struct my_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_stop (struct my_softc*) ; 

__attribute__((used)) static int
my_shutdown(device_t dev)
{
	struct my_softc *sc;

	sc = device_get_softc(dev);
	MY_LOCK(sc);
	my_stop(sc);
	MY_UNLOCK(sc);
	return 0;
}