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
typedef  int u_int32_t ;
struct aac_softc {int flags; int /*<<< orphan*/  aac_io_lock; struct aac_command* aac_commands; } ;
struct TYPE_2__ {int /*<<< orphan*/  XferState; } ;
struct aac_fib {scalar_t__ data; TYPE_1__ Header; } ;
struct aac_command {int /*<<< orphan*/  (* cm_complete ) (struct aac_command*) ;int /*<<< orphan*/  cm_flags; struct aac_fib* cm_fib; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_CLEAR_ISTATUS (struct aac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAC_CMD_COMPLETED ; 
 int /*<<< orphan*/  AAC_DB_RESPONSE_READY ; 
 int AAC_ERROR_NORMAL ; 
 int /*<<< orphan*/  AAC_FIBSTATE_DONEADAP ; 
 int AAC_GET_OUTB_QUEUE (struct aac_softc*) ; 
 int AAC_MEM1_GETREG4 (struct aac_softc*,int) ; 
 int AAC_QUEUE_FRZN ; 
 int /*<<< orphan*/  AAC_SET_OUTB_QUEUE (struct aac_softc*,int) ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  aac_handle_aif (struct aac_softc*,struct aac_fib*) ; 
 int /*<<< orphan*/  aac_remove_busy (struct aac_command*) ; 
 int /*<<< orphan*/  aac_startio (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_unmap_command (struct aac_command*) ; 
 int /*<<< orphan*/  free (struct aac_fib*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct aac_command*) ; 
 int /*<<< orphan*/  wakeup (struct aac_command*) ; 

void
aac_new_intr(void *arg)
{
	struct aac_softc *sc;
	u_int32_t index, fast;
	struct aac_command *cm;
	struct aac_fib *fib;
	int i;

	sc = (struct aac_softc *)arg;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	mtx_lock(&sc->aac_io_lock);
	while (1) {
		index = AAC_GET_OUTB_QUEUE(sc);
		if (index == 0xffffffff)
			index = AAC_GET_OUTB_QUEUE(sc);
		if (index == 0xffffffff)
			break;
		if (index & 2) {
			if (index == 0xfffffffe) {
				/* XXX This means that the controller wants
				 * more work.  Ignore it for now.
				 */
				continue;
			}
			/* AIF */
			fib = (struct aac_fib *)malloc(sizeof *fib, M_AACBUF,
				   M_NOWAIT | M_ZERO);
			if (fib == NULL) {
				/* If we're really this short on memory,
				 * hopefully breaking out of the handler will
				 * allow something to get freed.  This
				 * actually sucks a whole lot.
				 */
				break;
			}
			index &= ~2;
			for (i = 0; i < sizeof(struct aac_fib)/4; ++i)
				((u_int32_t *)fib)[i] = AAC_MEM1_GETREG4(sc, index + i*4);
			aac_handle_aif(sc, fib);
			free(fib, M_AACBUF);

			/*
			 * AIF memory is owned by the adapter, so let it
			 * know that we are done with it.
			 */
			AAC_SET_OUTB_QUEUE(sc, index);
			AAC_CLEAR_ISTATUS(sc, AAC_DB_RESPONSE_READY);
		} else {
			fast = index & 1;
			cm = sc->aac_commands + (index >> 2);
			fib = cm->cm_fib;
			if (fast) {
				fib->Header.XferState |= AAC_FIBSTATE_DONEADAP;
				*((u_int32_t *)(fib->data)) = AAC_ERROR_NORMAL;
			}
			aac_remove_busy(cm);
 			aac_unmap_command(cm);
			cm->cm_flags |= AAC_CMD_COMPLETED;

			/* is there a completion handler? */
			if (cm->cm_complete != NULL) {
				cm->cm_complete(cm);
			} else {
				/* assume that someone is sleeping on this
				 * command
				 */
				wakeup(cm);
			}
			sc->flags &= ~AAC_QUEUE_FRZN;
		}
	}
	/* see if we can start some more I/O */
	if ((sc->flags & AAC_QUEUE_FRZN) == 0)
		aac_startio(sc);

	mtx_unlock(&sc->aac_io_lock);
}