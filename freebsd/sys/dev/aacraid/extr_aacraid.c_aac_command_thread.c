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
struct aac_softc {int aifflags; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_io_lock; TYPE_1__* aac_common; int /*<<< orphan*/  aifthread; } ;
struct TYPE_2__ {scalar_t__* ac_printf; } ;

/* Variables and functions */
 int AAC_AIFFLAGS_ALLOCFIBS ; 
 int AAC_AIFFLAGS_EXIT ; 
 int AAC_AIFFLAGS_PENDING ; 
 int AAC_AIFFLAGS_RUNNING ; 
 int AAC_PERIODIC_INTERVAL ; 
 int EWOULDBLOCK ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  aac_alloc_commands (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_kthread_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_print_printf (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_timeout (struct aac_softc*) ; 
 int /*<<< orphan*/  aacraid_startio (struct aac_softc*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int hz ; 
 int msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aac_command_thread(struct aac_softc *sc)
{
	int retval;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	mtx_lock(&sc->aac_io_lock);
	sc->aifflags = AAC_AIFFLAGS_RUNNING;

	while ((sc->aifflags & AAC_AIFFLAGS_EXIT) == 0) {

		retval = 0;
		if ((sc->aifflags & AAC_AIFFLAGS_PENDING) == 0)
			retval = msleep(sc->aifthread, &sc->aac_io_lock, PRIBIO,
					"aacraid_aifthd", AAC_PERIODIC_INTERVAL * hz);

		/*
		 * First see if any FIBs need to be allocated.  This needs
		 * to be called without the driver lock because contigmalloc
		 * will grab Giant, and would result in an LOR.
		 */
		if ((sc->aifflags & AAC_AIFFLAGS_ALLOCFIBS) != 0) {
			aac_alloc_commands(sc);
			sc->aifflags &= ~AAC_AIFFLAGS_ALLOCFIBS;
			aacraid_startio(sc);
		}

		/*
		 * While we're here, check to see if any commands are stuck.
		 * This is pretty low-priority, so it's ok if it doesn't
		 * always fire.
		 */
		if (retval == EWOULDBLOCK)
			aac_timeout(sc);

		/* Check the hardware printf message buffer */
		if (sc->aac_common->ac_printf[0] != 0)
			aac_print_printf(sc);
	}
	sc->aifflags &= ~AAC_AIFFLAGS_RUNNING;
	mtx_unlock(&sc->aac_io_lock);
	wakeup(sc->aac_dev);

	aac_kthread_exit(0);
}