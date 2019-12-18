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
typedef  scalar_t__ uint32_t ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct hpet_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  mem_res; } ;
struct bintime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_MAIN_COUNTER ; 
 int /*<<< orphan*/  bintime2timespec (struct bintime*,struct timespec*) ; 
 int /*<<< orphan*/  bintime_sub (struct bintime*,struct bintime*) ; 
 int /*<<< orphan*/  binuptime (struct bintime*) ; 
 scalar_t__ bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void
hpet_test(struct hpet_softc *sc)
{
	int i;
	uint32_t u1, u2;
	struct bintime b0, b1, b2;
	struct timespec ts;

	binuptime(&b0);
	binuptime(&b0);
	binuptime(&b1);
	u1 = bus_read_4(sc->mem_res, HPET_MAIN_COUNTER);
	for (i = 1; i < 1000; i++)
		u2 = bus_read_4(sc->mem_res, HPET_MAIN_COUNTER);
	binuptime(&b2);
	u2 = bus_read_4(sc->mem_res, HPET_MAIN_COUNTER);

	bintime_sub(&b2, &b1);
	bintime_sub(&b1, &b0);
	bintime_sub(&b2, &b1);
	bintime2timespec(&b2, &ts);

	device_printf(sc->dev, "%ld.%09ld: %u ... %u = %u\n",
	    (long)ts.tv_sec, ts.tv_nsec, u1, u2, u2 - u1);

	device_printf(sc->dev, "time per call: %ld ns\n", ts.tv_nsec / 1000);
}