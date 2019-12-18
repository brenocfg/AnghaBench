#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct eventtimer {int /*<<< orphan*/  et_priv; } ;
struct attimer_softc {int intr_en; scalar_t__ period; int /*<<< orphan*/  mode; } ;
typedef  scalar_t__ sbintime_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {TYPE_1__* is_pic; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pic_enable_source ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_ONESHOT ; 
 int /*<<< orphan*/  MODE_PERIODIC ; 
 struct attimer_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_2__* i8254_intsrc ; 
 int /*<<< orphan*/  set_i8254_freq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int
attimer_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	device_t dev = (device_t)et->et_priv;
	struct attimer_softc *sc = device_get_softc(dev);

	if (period != 0) {
		sc->mode = MODE_PERIODIC;
		sc->period = period;
	} else {
		sc->mode = MODE_ONESHOT;
		sc->period = first;
	}
	if (!sc->intr_en) {
		i8254_intsrc->is_pic->pic_enable_source(i8254_intsrc);
		sc->intr_en = 1;
	}
	set_i8254_freq(sc->mode, sc->period);
	return (0);
}