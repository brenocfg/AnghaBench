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
struct eventtimer {int /*<<< orphan*/  et_priv; } ;
struct attimer_softc {scalar_t__ period; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_STOP ; 
 struct attimer_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_i8254_freq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
attimer_stop(struct eventtimer *et)
{
	device_t dev = (device_t)et->et_priv;
	struct attimer_softc *sc = device_get_softc(dev);
	
	sc->mode = MODE_STOP;
	sc->period = 0;
	set_i8254_freq(sc->mode, sc->period);
	return (0);
}