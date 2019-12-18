#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct aac_softc {int flags; int /*<<< orphan*/  aac_buffer_dmat; } ;
struct aac_sg_tableraw {int SgCount; TYPE_1__* SgEntryRaw; } ;
struct aac_sg_table64 {int SgCount; TYPE_3__* SgEntry64; } ;
struct aac_sg_table {int SgCount; TYPE_2__* SgEntry; } ;
struct aac_sg_entryraw {int dummy; } ;
struct aac_sg_entry64 {int dummy; } ;
struct aac_sg_entry {int dummy; } ;
struct TYPE_10__ {scalar_t__ Command; int Size; int SenderFibAddress; int SenderData; scalar_t__ ReceiverFibAddress; } ;
struct aac_fib {TYPE_4__ Header; } ;
struct aac_command {int cm_index; int cm_flags; int /*<<< orphan*/  cm_queue; int /*<<< orphan*/  cm_datamap; struct aac_fib* cm_fib; scalar_t__ cm_fibphys; struct aac_sg_table* cm_sgtable; struct aac_softc* cm_sc; } ;
struct TYPE_11__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;
struct TYPE_9__ {int /*<<< orphan*/  SgByteCount; int /*<<< orphan*/  SgAddress; } ;
struct TYPE_8__ {int /*<<< orphan*/  SgByteCount; int /*<<< orphan*/  SgAddress; } ;
struct TYPE_7__ {scalar_t__ Flags; scalar_t__ Prev; scalar_t__ Next; int /*<<< orphan*/  SgByteCount; int /*<<< orphan*/  SgAddress; } ;

/* Variables and functions */
 int AAC_CMD_DATAIN ; 
 int AAC_CMD_DATAOUT ; 
 int AAC_CMD_MAPPED ; 
 int AAC_FLAGS_NEW_COMM ; 
 int AAC_FLAGS_SG_64BIT ; 
 int AAC_QUEUE_FRZN ; 
 scalar_t__ AAC_SEND_COMMAND (struct aac_softc*,struct aac_command*) ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ EBUSY ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 scalar_t__ RawIo ; 
 scalar_t__ aac_enqueue_fib (struct aac_softc*,int /*<<< orphan*/ ,struct aac_command*) ; 
 int /*<<< orphan*/  aac_requeue_ready (struct aac_command*) ; 
 int /*<<< orphan*/  aac_unmap_command (struct aac_command*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static void
aac_map_command_sg(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct aac_softc *sc;
	struct aac_command *cm;
	struct aac_fib *fib;
	int i;

	cm = (struct aac_command *)arg;
	sc = cm->cm_sc;
	fib = cm->cm_fib;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* copy into the FIB */
	if (cm->cm_sgtable != NULL) {
		if (fib->Header.Command == RawIo) {
			struct aac_sg_tableraw *sg;
			sg = (struct aac_sg_tableraw *)cm->cm_sgtable;
			sg->SgCount = nseg;
			for (i = 0; i < nseg; i++) {
				sg->SgEntryRaw[i].SgAddress = segs[i].ds_addr;
				sg->SgEntryRaw[i].SgByteCount = segs[i].ds_len;
				sg->SgEntryRaw[i].Next = 0;
				sg->SgEntryRaw[i].Prev = 0;
				sg->SgEntryRaw[i].Flags = 0;
			}
			/* update the FIB size for the s/g count */
			fib->Header.Size += nseg*sizeof(struct aac_sg_entryraw);
		} else if ((cm->cm_sc->flags & AAC_FLAGS_SG_64BIT) == 0) {
			struct aac_sg_table *sg;
			sg = cm->cm_sgtable;
			sg->SgCount = nseg;
			for (i = 0; i < nseg; i++) {
				sg->SgEntry[i].SgAddress = segs[i].ds_addr;
				sg->SgEntry[i].SgByteCount = segs[i].ds_len;
			}
			/* update the FIB size for the s/g count */
			fib->Header.Size += nseg*sizeof(struct aac_sg_entry);
		} else {
			struct aac_sg_table64 *sg;
			sg = (struct aac_sg_table64 *)cm->cm_sgtable;
			sg->SgCount = nseg;
			for (i = 0; i < nseg; i++) {
				sg->SgEntry64[i].SgAddress = segs[i].ds_addr;
				sg->SgEntry64[i].SgByteCount = segs[i].ds_len;
			}
			/* update the FIB size for the s/g count */
			fib->Header.Size += nseg*sizeof(struct aac_sg_entry64);
		}
	}

	/* Fix up the address values in the FIB.  Use the command array index
	 * instead of a pointer since these fields are only 32 bits.  Shift
	 * the SenderFibAddress over to make room for the fast response bit
	 * and for the AIF bit
	 */
	cm->cm_fib->Header.SenderFibAddress = (cm->cm_index << 2);
	cm->cm_fib->Header.ReceiverFibAddress = (u_int32_t)cm->cm_fibphys;

	/* save a pointer to the command for speedy reverse-lookup */
	cm->cm_fib->Header.SenderData = cm->cm_index;

	if (cm->cm_flags & AAC_CMD_DATAIN)
		bus_dmamap_sync(sc->aac_buffer_dmat, cm->cm_datamap,
				BUS_DMASYNC_PREREAD);
	if (cm->cm_flags & AAC_CMD_DATAOUT)
		bus_dmamap_sync(sc->aac_buffer_dmat, cm->cm_datamap,
				BUS_DMASYNC_PREWRITE);
	cm->cm_flags |= AAC_CMD_MAPPED;

	if (sc->flags & AAC_FLAGS_NEW_COMM) {
		int count = 10000000L;
		while (AAC_SEND_COMMAND(sc, cm) != 0) {
			if (--count == 0) {
				aac_unmap_command(cm);
				sc->flags |= AAC_QUEUE_FRZN;
				aac_requeue_ready(cm);
			}
			DELAY(5);			/* wait 5 usec. */
		}
	} else {
		/* Put the FIB on the outbound queue */
		if (aac_enqueue_fib(sc, cm->cm_queue, cm) == EBUSY) {
			aac_unmap_command(cm);
			sc->flags |= AAC_QUEUE_FRZN;
			aac_requeue_ready(cm);
		}
	}
}