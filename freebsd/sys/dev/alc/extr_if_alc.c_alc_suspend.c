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
struct alc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_LOCK (struct alc_softc*) ; 
 int /*<<< orphan*/  ALC_UNLOCK (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_setwol (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_stop (struct alc_softc*) ; 
 struct alc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alc_suspend(device_t dev)
{
	struct alc_softc *sc;

	sc = device_get_softc(dev);

	ALC_LOCK(sc);
	alc_stop(sc);
	alc_setwol(sc);
	ALC_UNLOCK(sc);

	return (0);
}