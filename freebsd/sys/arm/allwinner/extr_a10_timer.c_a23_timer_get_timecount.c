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
typedef  scalar_t__ u_int ;
struct timecounter {scalar_t__ tc_priv; } ;
struct a10_timer_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_CURV_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_read_4 (struct a10_timer_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
a23_timer_get_timecount(struct timecounter *tc)
{
	struct a10_timer_softc *sc;
	uint32_t val;

	sc = (struct a10_timer_softc *)tc->tc_priv;
	if (sc == NULL)
		return (0);

	val = timer_read_4(sc, TIMER_CURV_REG(0));
	/* Counter count backwards */
	return (~0u - val);
}