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
struct rt1310_timer_softc {int dummy; } ;
struct eventtimer {scalar_t__ et_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TIMER_CONTROL ; 
 int /*<<< orphan*/  timer2_write_4 (struct rt1310_timer_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rt1310_timer_stop(struct eventtimer *et)
{
	struct rt1310_timer_softc *sc = (struct rt1310_timer_softc *)et->et_priv;

	timer2_write_4(sc, RT_TIMER_CONTROL, 0);

	return (0);
}