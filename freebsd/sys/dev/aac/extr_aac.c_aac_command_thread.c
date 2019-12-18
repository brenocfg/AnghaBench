#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct aac_softc {int aifflags; int flags; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_io_lock; TYPE_1__* aac_common; int /*<<< orphan*/  aifthread; } ;
struct TYPE_4__ {int Command; int XferState; scalar_t__ StructType; int Size; } ;
struct aac_fib {TYPE_2__ Header; scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__* ac_printf; } ;
typedef  int /*<<< orphan*/  AAC_FSAStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_ADAP_NORM_RESP_QUEUE ; 
 int AAC_AIFFLAGS_ALLOCFIBS ; 
 int AAC_AIFFLAGS_EXIT ; 
 int AAC_AIFFLAGS_PENDING ; 
 int AAC_AIFFLAGS_RUNNING ; 
 int AAC_FIBSTATE_DONEHOST ; 
 int AAC_FIBSTATE_FROMADAP ; 
 scalar_t__ AAC_FIBTYPE_TFIB ; 
 int AAC_FLAGS_NEW_COMM ; 
 int /*<<< orphan*/  AAC_HOST_NORM_CMD_QUEUE ; 
 int AAC_PERIODIC_INTERVAL ; 
 int /*<<< orphan*/  AAC_PRINT_FIB (struct aac_softc*,struct aac_fib*) ; 
#define  AifRequest 128 
 int EWOULDBLOCK ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  ST_OK ; 
 int /*<<< orphan*/  aac_alloc_commands (struct aac_softc*) ; 
 scalar_t__ aac_dequeue_fib (struct aac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct aac_fib**) ; 
 int /*<<< orphan*/  aac_enqueue_response (struct aac_softc*,int /*<<< orphan*/ ,struct aac_fib*) ; 
 int /*<<< orphan*/  aac_handle_aif (struct aac_softc*,struct aac_fib*) ; 
 int /*<<< orphan*/  aac_print_printf (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_startio (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_timeout (struct aac_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int hz ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aac_command_thread(struct aac_softc *sc)
{
	struct aac_fib *fib;
	u_int32_t fib_size;
	int size, retval;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	mtx_lock(&sc->aac_io_lock);
	sc->aifflags = AAC_AIFFLAGS_RUNNING;

	while ((sc->aifflags & AAC_AIFFLAGS_EXIT) == 0) {

		retval = 0;
		if ((sc->aifflags & AAC_AIFFLAGS_PENDING) == 0)
			retval = msleep(sc->aifthread, &sc->aac_io_lock, PRIBIO,
					"aifthd", AAC_PERIODIC_INTERVAL * hz);

		/*
		 * First see if any FIBs need to be allocated.  This needs
		 * to be called without the driver lock because contigmalloc
		 * can sleep.
		 */
		if ((sc->aifflags & AAC_AIFFLAGS_ALLOCFIBS) != 0) {
			mtx_unlock(&sc->aac_io_lock);
			aac_alloc_commands(sc);
			mtx_lock(&sc->aac_io_lock);
			sc->aifflags &= ~AAC_AIFFLAGS_ALLOCFIBS;
			aac_startio(sc);
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

		/* Also check to see if the adapter has a command for us. */
		if (sc->flags & AAC_FLAGS_NEW_COMM)
			continue;
		for (;;) {
			if (aac_dequeue_fib(sc, AAC_HOST_NORM_CMD_QUEUE,
					   &fib_size, &fib))
				break;

			AAC_PRINT_FIB(sc, fib);

			switch (fib->Header.Command) {
			case AifRequest:
				aac_handle_aif(sc, fib);
				break;
			default:
				device_printf(sc->aac_dev, "unknown command "
					      "from controller\n");
				break;
			}

			if ((fib->Header.XferState == 0) ||
			    (fib->Header.StructType != AAC_FIBTYPE_TFIB)) {
				break;
			}

			/* Return the AIF to the controller. */
			if (fib->Header.XferState & AAC_FIBSTATE_FROMADAP) {
				fib->Header.XferState |= AAC_FIBSTATE_DONEHOST;
				*(AAC_FSAStatus*)fib->data = ST_OK;

				/* XXX Compute the Size field? */
				size = fib->Header.Size;
				if (size > sizeof(struct aac_fib)) {
					size = sizeof(struct aac_fib);
					fib->Header.Size = size;
				}
				/*
				 * Since we did not generate this command, it
				 * cannot go through the normal
				 * enqueue->startio chain.
				 */
				aac_enqueue_response(sc,
						 AAC_ADAP_NORM_RESP_QUEUE,
						 fib);
			}
		}
	}
	sc->aifflags &= ~AAC_AIFFLAGS_RUNNING;
	mtx_unlock(&sc->aac_io_lock);
	wakeup(sc->aac_dev);

	kproc_exit(0);
}