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
struct aac_softc {int /*<<< orphan*/  aac_io_lock; } ;
struct aac_command {struct aac_softc* cm_sc; } ;

/* Variables and functions */
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  aac_enqueue_ready (struct aac_command*) ; 
 int /*<<< orphan*/  aacraid_startio (struct aac_softc*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int msleep (struct aac_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
aacraid_wait_command(struct aac_command *cm)
{
	struct aac_softc *sc;
	int error;

	sc = cm->cm_sc;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	mtx_assert(&sc->aac_io_lock, MA_OWNED);

	/* Put the command on the ready queue and get things going */
	aac_enqueue_ready(cm);
	aacraid_startio(sc);
	error = msleep(cm, &sc->aac_io_lock, PRIBIO, "aacraid_wait", 0);
	return(error);
}