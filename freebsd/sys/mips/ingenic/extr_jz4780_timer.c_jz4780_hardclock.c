#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct jz4780_timer_softc {TYPE_1__ et; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct jz4780_timer_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  JZ_TC_TECR ; 
 int /*<<< orphan*/  JZ_TC_TFCR ; 
 int /*<<< orphan*/  TESR_TCST5 ; 
 int /*<<< orphan*/  TFR_FFLAG5 ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_hardclock(void *arg)
{
	struct jz4780_timer_softc *sc = (struct jz4780_timer_softc *)arg;

	CSR_WRITE_4(sc, JZ_TC_TFCR, TFR_FFLAG5);
	CSR_WRITE_4(sc, JZ_TC_TECR, TESR_TCST5);

	if (sc->et.et_active)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);

	return (FILTER_HANDLED);
}