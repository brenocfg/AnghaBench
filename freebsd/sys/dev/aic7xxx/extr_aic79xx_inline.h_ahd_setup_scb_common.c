#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scb {int flags; int /*<<< orphan*/  sense_busaddr; TYPE_4__* hscb; scalar_t__ crc_retry_count; } ;
struct ahd_softc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sense_addr; } ;
struct TYPE_6__ {TYPE_1__ cdb_plus_saddr; } ;
struct TYPE_7__ {TYPE_2__ idata; } ;
struct TYPE_8__ {int task_attribute; int control; int cdb_len; TYPE_3__ shared_data; } ;

/* Variables and functions */
 int MAX_CDB_LEN_WITH_SENSE_ADDR ; 
 int SCB_CDB_LEN_PTR ; 
 int SCB_PACKETIZED ; 
 int SCB_TAG_TYPE ; 
 int SCB_XFERLEN_ODD ; 
 int aic_get_transfer_length (struct scb*) ; 
 int /*<<< orphan*/  aic_htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ahd_setup_scb_common(struct ahd_softc *ahd, struct scb *scb)
{
	/* XXX Handle target mode SCBs. */
	scb->crc_retry_count = 0;
	if ((scb->flags & SCB_PACKETIZED) != 0) {
		/* XXX what about ACA??  It is type 4, but TAG_TYPE == 0x3. */
		scb->hscb->task_attribute = scb->hscb->control & SCB_TAG_TYPE;
	} else {
		if (aic_get_transfer_length(scb) & 0x01)
			scb->hscb->task_attribute = SCB_XFERLEN_ODD;
		else
			scb->hscb->task_attribute = 0;
	}

	if (scb->hscb->cdb_len <= MAX_CDB_LEN_WITH_SENSE_ADDR
	 || (scb->hscb->cdb_len & SCB_CDB_LEN_PTR) != 0)
		scb->hscb->shared_data.idata.cdb_plus_saddr.sense_addr =
		    aic_htole32(scb->sense_busaddr);
}