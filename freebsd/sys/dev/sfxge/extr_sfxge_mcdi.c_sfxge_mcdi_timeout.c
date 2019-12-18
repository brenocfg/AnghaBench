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
struct sfxge_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFSYS_PROBE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcdi_timeout ; 
 int /*<<< orphan*/  sfxge_schedule_reset (struct sfxge_softc*) ; 

__attribute__((used)) static void
sfxge_mcdi_timeout(struct sfxge_softc *sc)
{
	device_t dev = sc->dev;

	log(LOG_WARNING, "[%s%d] MC_TIMEOUT", device_get_name(dev),
		device_get_unit(dev));

	EFSYS_PROBE(mcdi_timeout);
	sfxge_schedule_reset(sc);
}