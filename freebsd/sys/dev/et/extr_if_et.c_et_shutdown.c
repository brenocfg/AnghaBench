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
struct et_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ET_LOCK (struct et_softc*) ; 
 int /*<<< orphan*/  ET_UNLOCK (struct et_softc*) ; 
 struct et_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et_stop (struct et_softc*) ; 

__attribute__((used)) static int
et_shutdown(device_t dev)
{
	struct et_softc *sc;

	sc = device_get_softc(dev);
	ET_LOCK(sc);
	et_stop(sc);
	ET_UNLOCK(sc);
	return (0);
}