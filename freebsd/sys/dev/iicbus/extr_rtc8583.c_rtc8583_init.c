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
struct rtc8583_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  init_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKF_SETTIME_NO_ADJ ; 
 int /*<<< orphan*/  clock_register_flags (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_schedule (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtc8583_init(void *arg)
{
	struct rtc8583_softc	*sc;
	
	sc = (struct rtc8583_softc*)arg;
	config_intrhook_disestablish(&sc->init_hook);

	/*
	 * Register as a system realtime clock.
	 */
	clock_register_flags(sc->dev, 1000000, CLOCKF_SETTIME_NO_ADJ);
	clock_schedule(sc->dev, 1);
	return;
}