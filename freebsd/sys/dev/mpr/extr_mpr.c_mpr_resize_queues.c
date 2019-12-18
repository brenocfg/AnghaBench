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
typedef  int u_int ;
struct mpr_softc {int num_reqs; int num_prireqs; int max_replyframes; int max_evtframes; int reqframesz; int chain_frame_size; int max_io_pages; int maxio; int num_chains; scalar_t__ max_chains; int msi_msgs; scalar_t__ num_replies; TYPE_1__* facts; int /*<<< orphan*/  max_reqframes; int /*<<< orphan*/  max_prireqframes; } ;
struct TYPE_2__ {int HighPriorityCredit; int RequestCredit; int MaxReplyDescriptorPostQueueDepth; int IOCRequestFrameSize; scalar_t__ MsgVersion; int MaxChainDepth; int MaxMSIxVectors; int /*<<< orphan*/  IOCMaxChainSegmentSize; } ;
typedef  int /*<<< orphan*/  MPI2_IEEE_SGE_SIMPLE64 ;

/* Variables and functions */
 int MAX (int,int /*<<< orphan*/ ) ; 
 int MAXPHYS ; 
 void* MIN (int,int) ; 
 scalar_t__ MPI2_VERSION_02_05 ; 
 int MPR_DEFAULT_CHAIN_SEG_SIZE ; 
 int /*<<< orphan*/  MPR_INIT ; 
 int MPR_MAX_CHAIN_ELEMENT_SIZE ; 
 int PAGE_SIZE ; 
 int htole16 (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*,int,int,scalar_t__) ; 

__attribute__((used)) static void
mpr_resize_queues(struct mpr_softc *sc)
{
	u_int reqcr, prireqcr, maxio, sges_per_frame, chain_seg_size;

	/*
	 * Size the queues. Since the reply queues always need one free
	 * entry, we'll deduct one reply message here.  The LSI documents
	 * suggest instead to add a count to the request queue, but I think
	 * that it's better to deduct from reply queue.
	 */
	prireqcr = MAX(1, sc->max_prireqframes);
	prireqcr = MIN(prireqcr, sc->facts->HighPriorityCredit);

	reqcr = MAX(2, sc->max_reqframes);
	reqcr = MIN(reqcr, sc->facts->RequestCredit);

	sc->num_reqs = prireqcr + reqcr;
	sc->num_prireqs = prireqcr;
	sc->num_replies = MIN(sc->max_replyframes + sc->max_evtframes,
	    sc->facts->MaxReplyDescriptorPostQueueDepth) - 1;

	/* Store the request frame size in bytes rather than as 32bit words */
	sc->reqframesz = sc->facts->IOCRequestFrameSize * 4;

	/*
	 * Gen3 and beyond uses the IOCMaxChainSegmentSize from IOC Facts to
	 * get the size of a Chain Frame.  Previous versions use the size as a
	 * Request Frame for the Chain Frame size.  If IOCMaxChainSegmentSize
	 * is 0, use the default value.  The IOCMaxChainSegmentSize is the
	 * number of 16-byte elelements that can fit in a Chain Frame, which is
	 * the size of an IEEE Simple SGE.
	 */
	if (sc->facts->MsgVersion >= MPI2_VERSION_02_05) {
		chain_seg_size = htole16(sc->facts->IOCMaxChainSegmentSize);
		if (chain_seg_size == 0)
			chain_seg_size = MPR_DEFAULT_CHAIN_SEG_SIZE;
		sc->chain_frame_size = chain_seg_size *
		    MPR_MAX_CHAIN_ELEMENT_SIZE;
	} else {
		sc->chain_frame_size = sc->reqframesz;
	}

	/*
	 * Max IO Size is Page Size * the following:
	 * ((SGEs per frame - 1 for chain element) * Max Chain Depth)
	 * + 1 for no chain needed in last frame
	 *
	 * If user suggests a Max IO size to use, use the smaller of the
	 * user's value and the calculated value as long as the user's
	 * value is larger than 0. The user's value is in pages.
	 */
	sges_per_frame = sc->chain_frame_size/sizeof(MPI2_IEEE_SGE_SIMPLE64)-1;
	maxio = (sges_per_frame * sc->facts->MaxChainDepth + 1) * PAGE_SIZE;

	/*
	 * If I/O size limitation requested then use it and pass up to CAM.
	 * If not, use MAXPHYS as an optimization hint, but report HW limit.
	 */
	if (sc->max_io_pages > 0) {
		maxio = min(maxio, sc->max_io_pages * PAGE_SIZE);
		sc->maxio = maxio;
	} else {
		sc->maxio = maxio;
		maxio = min(maxio, MAXPHYS);
	}

	sc->num_chains = (maxio / PAGE_SIZE + sges_per_frame - 2) /
	    sges_per_frame * reqcr;
	if (sc->max_chains > 0 && sc->max_chains < sc->num_chains)
		sc->num_chains = sc->max_chains;

	/*
	 * Figure out the number of MSIx-based queues.  If the firmware or
	 * user has done something crazy and not allowed enough credit for
	 * the queues to be useful then don't enable multi-queue.
	 */
	if (sc->facts->MaxMSIxVectors < 2)
		sc->msi_msgs = 1;

	if (sc->msi_msgs > 1) {
		sc->msi_msgs = MIN(sc->msi_msgs, mp_ncpus);
		sc->msi_msgs = MIN(sc->msi_msgs, sc->facts->MaxMSIxVectors);
		if (sc->num_reqs / sc->msi_msgs < 2)
			sc->msi_msgs = 1;
	}

	mpr_dprint(sc, MPR_INIT, "Sized queues to q=%d reqs=%d replies=%d\n",
	    sc->msi_msgs, sc->num_reqs, sc->num_replies);
}