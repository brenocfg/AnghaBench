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
typedef  int /*<<< orphan*/  u_int ;
struct timecounter {struct hpet_softc* tc_priv; } ;
struct hpet_softc {int /*<<< orphan*/  mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_MAIN_COUNTER ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
hpet_get_timecount(struct timecounter *tc)
{
	struct hpet_softc *sc;

	sc = tc->tc_priv;
	return (bus_read_4(sc->mem_res, HPET_MAIN_COUNTER));
}