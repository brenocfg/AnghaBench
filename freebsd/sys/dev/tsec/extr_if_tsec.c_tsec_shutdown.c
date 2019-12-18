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
struct tsec_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TSEC_GLOBAL_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_GLOBAL_UNLOCK (struct tsec_softc*) ; 
 struct tsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsec_stop (struct tsec_softc*) ; 

int
tsec_shutdown(device_t dev)
{
	struct tsec_softc *sc;

	sc = device_get_softc(dev);

	TSEC_GLOBAL_LOCK(sc);
	tsec_stop(sc);
	TSEC_GLOBAL_UNLOCK(sc);
	return (0);
}