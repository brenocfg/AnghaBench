#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct runl {int dummy; } ;
struct tpc_list {scalar_t__ stage; scalar_t__ cursectors; scalar_t__ segsectors; int tbdio; int nrange; scalar_t__ segbytes; TYPE_4__* lun; TYPE_3__* range; struct runl allio; scalar_t__ curbytes; TYPE_9__* ctsio; int /*<<< orphan*/  fwd_sense_len; int /*<<< orphan*/  fwd_sense_data; scalar_t__ fwd_scsi_status; scalar_t__ error; scalar_t__ abort; } ;
struct tpc_io {int /*<<< orphan*/  lun; TYPE_7__* io; struct runl run; struct tpc_list* list; } ;
struct TYPE_13__ {int status; } ;
struct TYPE_20__ {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; scalar_t__ scsi_status; TYPE_1__ io_hdr; } ;
struct TYPE_18__ {int retries; TYPE_5__* ctl_private; } ;
struct TYPE_19__ {TYPE_6__ io_hdr; } ;
struct TYPE_17__ {struct tpc_io* ptr; } ;
struct TYPE_16__ {int /*<<< orphan*/  lun; TYPE_2__* be_lun; } ;
struct TYPE_15__ {int /*<<< orphan*/  lba; int /*<<< orphan*/  length; } ;
struct TYPE_14__ {scalar_t__ blocksize; } ;

/* Variables and functions */
 int CTL_AUTOSENSE ; 
 size_t CTL_PRIV_FRONTEND ; 
 int CTL_RETVAL_COMPLETE ; 
 int CTL_RETVAL_ERROR ; 
 int CTL_RETVAL_QUEUED ; 
 int CTL_SCSI_ERROR ; 
 int /*<<< orphan*/  CTL_TAG_SIMPLE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SWS_NDOB ; 
 scalar_t__ TAILQ_EMPTY (struct runl*) ; 
 struct tpc_io* TAILQ_FIRST (struct runl*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct runl*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct runl*,struct tpc_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct runl*,struct tpc_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_free_io (TYPE_7__*) ; 
 int /*<<< orphan*/  ctl_scsi_write_same (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_task_aborted (TYPE_9__*) ; 
 int /*<<< orphan*/  free (struct tpc_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 struct tpc_io* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rlinks ; 
 scalar_t__ scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_8btou64 (int /*<<< orphan*/ ) ; 
 TYPE_7__* tpcl_alloc_io () ; 
 int tpcl_queue (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tpc_process_zero_wut(struct tpc_list *list)
{
	struct tpc_io *tio, *tiow;
	struct runl run, *prun;
	int r;
	uint32_t dstblock, len;

	if (list->stage > 0) {
complete:
		/* Cleanup after previous rounds. */
		while ((tio = TAILQ_FIRST(&list->allio)) != NULL) {
			TAILQ_REMOVE(&list->allio, tio, links);
			ctl_free_io(tio->io);
			free(tio, M_CTL);
		}
		if (list->abort) {
			ctl_set_task_aborted(list->ctsio);
			return (CTL_RETVAL_ERROR);
		} else if (list->error) {
			if (list->fwd_scsi_status) {
				list->ctsio->io_hdr.status =
				    CTL_SCSI_ERROR | CTL_AUTOSENSE;
				list->ctsio->scsi_status = list->fwd_scsi_status;
				list->ctsio->sense_data = list->fwd_sense_data;
				list->ctsio->sense_len = list->fwd_sense_len;
			} else {
				ctl_set_invalid_field(list->ctsio,
				    /*sks_valid*/ 0, /*command*/ 0,
				    /*field*/ 0, /*bit_valid*/ 0, /*bit*/ 0);
			}
			return (CTL_RETVAL_ERROR);
		}
		list->cursectors += list->segsectors;
		list->curbytes += list->segbytes;
		return (CTL_RETVAL_COMPLETE);
	}

	dstblock = list->lun->be_lun->blocksize;
	TAILQ_INIT(&run);
	prun = &run;
	list->tbdio = 1;
	TAILQ_INIT(&list->allio);
	list->segsectors = 0;
	for (r = 0; r < list->nrange; r++) {
		len = scsi_4btoul(list->range[r].length);
		if (len == 0)
			continue;

		tiow = malloc(sizeof(*tiow), M_CTL, M_WAITOK | M_ZERO);
		TAILQ_INIT(&tiow->run);
		tiow->list = list;
		TAILQ_INSERT_TAIL(&list->allio, tiow, links);
		tiow->io = tpcl_alloc_io();
		ctl_scsi_write_same(tiow->io,
				    /*data_ptr*/ NULL,
				    /*data_len*/ 0,
				    /*byte2*/ SWS_NDOB,
				    /*lba*/ scsi_8btou64(list->range[r].lba),
				    /*num_blocks*/ len,
				    /*tag_type*/ CTL_TAG_SIMPLE,
				    /*control*/ 0);
		tiow->io->io_hdr.retries = 3;
		tiow->lun = list->lun->lun;
		tiow->io->io_hdr.ctl_private[CTL_PRIV_FRONTEND].ptr = tiow;

		TAILQ_INSERT_TAIL(prun, tiow, rlinks);
		prun = &tiow->run;
		list->segsectors += len;
	}
	list->segbytes = list->segsectors * dstblock;

	if (TAILQ_EMPTY(&run))
		goto complete;

	while ((tiow = TAILQ_FIRST(&run)) != NULL) {
		TAILQ_REMOVE(&run, tiow, rlinks);
		if (tpcl_queue(tiow->io, tiow->lun) != CTL_RETVAL_COMPLETE)
			panic("tpcl_queue() error");
	}

	list->stage++;
	return (CTL_RETVAL_QUEUED);
}