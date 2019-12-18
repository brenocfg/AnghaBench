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
typedef  int uint16_t ;
struct ichwd_softc {int active; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCO1_CNT ; 
 int TCO_CNT_PRESERVE ; 
 int TCO_TMR_HALT ; 
 int ichwd_read_tco_2 (struct ichwd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichwd_verbose_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ichwd_write_tco_2 (struct ichwd_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
ichwd_tmr_enable(struct ichwd_softc *sc)
{
	uint16_t cnt;

	cnt = ichwd_read_tco_2(sc, TCO1_CNT) & TCO_CNT_PRESERVE;
	ichwd_write_tco_2(sc, TCO1_CNT, cnt & ~TCO_TMR_HALT);
	sc->active = 1;
	ichwd_verbose_printf(sc->device, "timer enabled\n");
}