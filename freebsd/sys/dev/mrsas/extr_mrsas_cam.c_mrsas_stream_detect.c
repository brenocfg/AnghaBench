#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct mrsas_softc {TYPE_5__** streamDetectByLD; } ;
struct mrsas_mpt_cmd {TYPE_3__* io_request; } ;
struct IO_REQUEST_INFO {size_t ldTgtId; scalar_t__ ldStartBlock; scalar_t__ isRead; scalar_t__ numBlocks; } ;
typedef  int boolean_t ;
struct TYPE_10__ {size_t mruBitMap; TYPE_4__* streamTrack; } ;
struct TYPE_9__ {scalar_t__ nextSeqLBA; scalar_t__ isRead; } ;
struct TYPE_6__ {int /*<<< orphan*/  streamDetected; } ;
struct TYPE_7__ {TYPE_1__ raid_context_g35; } ;
struct TYPE_8__ {TYPE_2__ RaidContext; } ;
typedef  TYPE_4__ STREAM_DETECT ;
typedef  TYPE_5__ LD_STREAM_DETECT ;

/* Variables and functions */
 int BITS_PER_INDEX_STREAM ; 
 int MAX_STREAMS_TRACKED ; 
 size_t STREAM_MASK ; 
 int /*<<< orphan*/  TRUE ; 
 size_t ZERO_LAST_STREAM ; 

__attribute__((used)) static void
mrsas_stream_detect(struct mrsas_softc *sc, struct mrsas_mpt_cmd *cmd,
    struct IO_REQUEST_INFO *io_info)
{
	u_int32_t device_id = io_info->ldTgtId;
	LD_STREAM_DETECT *current_ld_SD = sc->streamDetectByLD[device_id];
	u_int32_t *track_stream = &current_ld_SD->mruBitMap;
	u_int32_t streamNum, shiftedValues, unshiftedValues;
	u_int32_t indexValueMask, shiftedValuesMask;
	int i;
	boolean_t isReadAhead = false;
	STREAM_DETECT *current_SD;

	/* find possible stream */
	for (i = 0; i < MAX_STREAMS_TRACKED; ++i) {
		streamNum = (*track_stream >> (i * BITS_PER_INDEX_STREAM)) &
				STREAM_MASK;
		current_SD = &current_ld_SD->streamTrack[streamNum];
		/*
		 * if we found a stream, update the raid context and
		 * also update the mruBitMap
		 */
		if (current_SD->nextSeqLBA &&
		    io_info->ldStartBlock >= current_SD->nextSeqLBA &&
		    (io_info->ldStartBlock <= (current_SD->nextSeqLBA+32)) &&
		    (current_SD->isRead == io_info->isRead)) {
			if (io_info->ldStartBlock != current_SD->nextSeqLBA &&
			    (!io_info->isRead || !isReadAhead)) {
				/*
				 * Once the API availible we need to change this.
				 * At this point we are not allowing any gap
				 */
				continue;
			}
			cmd->io_request->RaidContext.raid_context_g35.streamDetected = TRUE;
			current_SD->nextSeqLBA = io_info->ldStartBlock + io_info->numBlocks;
			/*
			 * update the mruBitMap LRU
			 */
			shiftedValuesMask = (1 << i * BITS_PER_INDEX_STREAM) - 1 ;
			shiftedValues = ((*track_stream & shiftedValuesMask) <<
			    BITS_PER_INDEX_STREAM);
			indexValueMask = STREAM_MASK << i * BITS_PER_INDEX_STREAM;
			unshiftedValues = (*track_stream) &
			    (~(shiftedValuesMask | indexValueMask));
			*track_stream =
			    (unshiftedValues | shiftedValues | streamNum);
			return;
		}
	}
	/*
	 * if we did not find any stream, create a new one from the least recently used
	 */
	streamNum = (*track_stream >>
	    ((MAX_STREAMS_TRACKED - 1) * BITS_PER_INDEX_STREAM)) & STREAM_MASK;
	current_SD = &current_ld_SD->streamTrack[streamNum];
	current_SD->isRead = io_info->isRead;
	current_SD->nextSeqLBA = io_info->ldStartBlock + io_info->numBlocks;
	*track_stream = (((*track_stream & ZERO_LAST_STREAM) << 4) | streamNum);
	return;
}