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
struct timecounter {struct schizo_softc* tc_priv; } ;
struct schizo_softc {int dummy; } ;

/* Variables and functions */
 int SCHIZO_CTRL_READ_8 (struct schizo_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STX_CTRL_PERF_CNT ; 
 int STX_CTRL_PERF_CNT_CNT0_SHIFT ; 
 int STX_CTRL_PERF_CNT_MASK ; 

__attribute__((used)) static u_int
schizo_get_timecount(struct timecounter *tc)
{
	struct schizo_softc *sc;

	sc = tc->tc_priv;
	return ((SCHIZO_CTRL_READ_8(sc, STX_CTRL_PERF_CNT) &
	    (STX_CTRL_PERF_CNT_MASK << STX_CTRL_PERF_CNT_CNT0_SHIFT)) >>
	    STX_CTRL_PERF_CNT_CNT0_SHIFT);
}