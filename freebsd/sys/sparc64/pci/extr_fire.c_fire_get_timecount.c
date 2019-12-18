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
typedef  int u_int ;
struct timecounter {struct fire_softc* tc_priv; } ;
struct fire_softc {int dummy; } ;

/* Variables and functions */
 int FIRE_CTRL_READ_8 (struct fire_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FO_XBC_PRF_CNT0 ; 
 int TC_COUNTER_MAX_MASK ; 

__attribute__((used)) static u_int
fire_get_timecount(struct timecounter *tc)
{
	struct fire_softc *sc;

	sc = tc->tc_priv;
	return (FIRE_CTRL_READ_8(sc, FO_XBC_PRF_CNT0) & TC_COUNTER_MAX_MASK);
}