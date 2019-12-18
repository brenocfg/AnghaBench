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
struct timecounter {scalar_t__ tc_priv; } ;
struct jz4780_timer_softc {int dummy; } ;

/* Variables and functions */
 int CSR_READ_4 (struct jz4780_timer_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_OST_CNT_LO ; 

__attribute__((used)) static unsigned
jz4780_get_timecount(struct timecounter *tc)
{
	struct jz4780_timer_softc *sc =
	    (struct jz4780_timer_softc *)tc->tc_priv;

	return CSR_READ_4(sc, JZ_OST_CNT_LO);
}