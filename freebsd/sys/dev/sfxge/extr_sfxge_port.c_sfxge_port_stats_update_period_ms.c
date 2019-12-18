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
struct sfxge_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int UINT16_MAX ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int sfxge_stats_update_period_ms ; 

__attribute__((used)) static uint16_t
sfxge_port_stats_update_period_ms(struct sfxge_softc *sc)
{
	int period_ms = sfxge_stats_update_period_ms;

	if (period_ms < 0) {
		device_printf(sc->dev,
			"treat negative stats update period %d as 0 (disable)\n",
			 period_ms);
		period_ms = 0;
	} else if (period_ms > UINT16_MAX) {
		device_printf(sc->dev,
			"treat too big stats update period %d as %u\n",
			period_ms, UINT16_MAX);
		period_ms = UINT16_MAX;
	}

	return period_ms;
}