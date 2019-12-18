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
typedef  int /*<<< orphan*/  tmpstr ;
struct mrsas_softc {int mrsas_debug; int mrsas_fw_fault_check_delay; int drv_stream_detection; int lb_pending_cmds; int /*<<< orphan*/  mrsas_dev; scalar_t__ block_sync_cache; scalar_t__ reset_in_progress; scalar_t__ reset_count; int /*<<< orphan*/  mrsas_io_timeout; } ;

/* Variables and functions */
 int MRSAS_AEN ; 
 int MRSAS_FAULT ; 
 int MRSAS_INFO ; 
 int /*<<< orphan*/  MRSAS_IO_TIMEOUT ; 
 int MRSAS_OCR ; 
 int MRSAS_TRACE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
mrsas_get_tunables(struct mrsas_softc *sc)
{
	char tmpstr[80];

	/* XXX default to some debugging for now */
	sc->mrsas_debug =
		(MRSAS_FAULT | MRSAS_OCR | MRSAS_INFO | MRSAS_TRACE | MRSAS_AEN);
	sc->mrsas_io_timeout = MRSAS_IO_TIMEOUT;
	sc->mrsas_fw_fault_check_delay = 1;
	sc->reset_count = 0;
	sc->reset_in_progress = 0;
	sc->block_sync_cache = 0;
	sc->drv_stream_detection = 1;

	/*
	 * Grab the global variables.
	 */
	TUNABLE_INT_FETCH("hw.mrsas.debug_level", &sc->mrsas_debug);

	/*
	 * Grab the global variables.
	 */
	TUNABLE_INT_FETCH("hw.mrsas.lb_pending_cmds", &sc->lb_pending_cmds);

	/* Grab the unit-instance variables */
	snprintf(tmpstr, sizeof(tmpstr), "dev.mrsas.%d.debug_level",
	    device_get_unit(sc->mrsas_dev));
	TUNABLE_INT_FETCH(tmpstr, &sc->mrsas_debug);
}