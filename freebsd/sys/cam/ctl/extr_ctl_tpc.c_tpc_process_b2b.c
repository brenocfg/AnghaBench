#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct runl {int dummy; } ;
struct tpc_list {size_t curseg; int stage; int cursectors; int segsectors; int curbytes; int segbytes; scalar_t__ tbdio; struct runl allio; int /*<<< orphan*/  ctsio; TYPE_3__* cscd; scalar_t__* seg; scalar_t__ error; scalar_t__ abort; } ;
struct tpc_io {size_t cscd; scalar_t__ lun; TYPE_4__* io; struct runl run; int /*<<< orphan*/  target; struct tpc_io* buf; struct tpc_list* list; } ;
struct scsi_ec_segment_b2b {int flags; int /*<<< orphan*/  dst_lba; int /*<<< orphan*/  src_lba; int /*<<< orphan*/  number_of_blocks; int /*<<< orphan*/  dst_cscd; int /*<<< orphan*/  src_cscd; } ;
struct scsi_ec_cscd_dtsp {int /*<<< orphan*/  block_length; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  csi ;
struct TYPE_8__ {int retries; TYPE_1__* ctl_private; } ;
struct TYPE_10__ {TYPE_2__ io_hdr; } ;
struct TYPE_9__ {struct scsi_ec_cscd_dtsp dtsp; } ;
struct TYPE_7__ {struct tpc_io* ptr; } ;

/* Variables and functions */
 size_t CTL_PRIV_FRONTEND ; 
 int CTL_RETVAL_COMPLETE ; 
 int CTL_RETVAL_ERROR ; 
 int CTL_RETVAL_QUEUED ; 
 int /*<<< orphan*/  CTL_TAG_SIMPLE ; 
 int EC_SEG_DC ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SSD_ELEM_COMMAND ; 
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_FORWARDED_SDS_EXDST ; 
 int /*<<< orphan*/  SSD_FORWARDED_SDS_EXSRC ; 
 int /*<<< orphan*/  SSD_KEY_COPY_ABORTED ; 
 struct tpc_io* TAILQ_FIRST (struct runl*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct runl*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct runl*,struct tpc_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct runl*,struct tpc_io*,int /*<<< orphan*/ ) ; 
 int TPC_MAX_IO_SIZE ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  ctl_free_io (TYPE_4__*) ; 
 int /*<<< orphan*/  ctl_scsi_read_write (TYPE_4__*,struct tpc_io*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_sense (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_task_aborted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tpc_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rlinks ; 
 void* scsi_2btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_3btoul (int /*<<< orphan*/ ) ; 
 int scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ tpc_resolve (struct tpc_list*,size_t,int*,int*,int*) ; 
 int /*<<< orphan*/  tpc_set_io_error_sense (struct tpc_list*) ; 
 void* tpcl_alloc_io () ; 
 int tpcl_queue (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int
tpc_process_b2b(struct tpc_list *list)
{
	struct scsi_ec_segment_b2b *seg;
	struct scsi_ec_cscd_dtsp *sdstp, *ddstp;
	struct tpc_io *tior, *tiow;
	struct runl run;
	uint64_t sl, dl;
	off_t srclba, dstlba, numbytes, donebytes, roundbytes;
	int numlba;
	uint32_t srcblock, dstblock, pb, pbo, adj;
	uint16_t scscd, dcscd;
	uint8_t csi[4];

	scsi_ulto4b(list->curseg, csi);
	if (list->stage == 1) {
		while ((tior = TAILQ_FIRST(&list->allio)) != NULL) {
			TAILQ_REMOVE(&list->allio, tior, links);
			ctl_free_io(tior->io);
			free(tior->buf, M_CTL);
			free(tior, M_CTL);
		}
		if (list->abort) {
			ctl_set_task_aborted(list->ctsio);
			return (CTL_RETVAL_ERROR);
		} else if (list->error) {
			tpc_set_io_error_sense(list);
			return (CTL_RETVAL_ERROR);
		}
		list->cursectors += list->segsectors;
		list->curbytes += list->segbytes;
		return (CTL_RETVAL_COMPLETE);
	}

	TAILQ_INIT(&list->allio);
	seg = (struct scsi_ec_segment_b2b *)list->seg[list->curseg];
	scscd = scsi_2btoul(seg->src_cscd);
	dcscd = scsi_2btoul(seg->dst_cscd);
	sl = tpc_resolve(list, scscd, &srcblock, NULL, NULL);
	dl = tpc_resolve(list, dcscd, &dstblock, &pb, &pbo);
	if (sl == UINT64_MAX || dl == UINT64_MAX) {
		ctl_set_sense(list->ctsio, /*current_error*/ 1,
		    /*sense_key*/ SSD_KEY_COPY_ABORTED,
		    /*asc*/ 0x08, /*ascq*/ 0x04,
		    SSD_ELEM_COMMAND, sizeof(csi), csi,
		    SSD_ELEM_NONE);
		return (CTL_RETVAL_ERROR);
	}
	if (pbo > 0)
		pbo = pb - pbo;
	sdstp = &list->cscd[scscd].dtsp;
	if (scsi_3btoul(sdstp->block_length) != 0)
		srcblock = scsi_3btoul(sdstp->block_length);
	ddstp = &list->cscd[dcscd].dtsp;
	if (scsi_3btoul(ddstp->block_length) != 0)
		dstblock = scsi_3btoul(ddstp->block_length);
	numlba = scsi_2btoul(seg->number_of_blocks);
	if (seg->flags & EC_SEG_DC)
		numbytes = (off_t)numlba * dstblock;
	else
		numbytes = (off_t)numlba * srcblock;
	srclba = scsi_8btou64(seg->src_lba);
	dstlba = scsi_8btou64(seg->dst_lba);

//	printf("Copy %ju bytes from %ju @ %ju to %ju @ %ju\n",
//	    (uintmax_t)numbytes, sl, scsi_8btou64(seg->src_lba),
//	    dl, scsi_8btou64(seg->dst_lba));

	if (numbytes == 0)
		return (CTL_RETVAL_COMPLETE);

	if (numbytes % srcblock != 0 || numbytes % dstblock != 0) {
		ctl_set_sense(list->ctsio, /*current_error*/ 1,
		    /*sense_key*/ SSD_KEY_COPY_ABORTED,
		    /*asc*/ 0x26, /*ascq*/ 0x0A,
		    SSD_ELEM_COMMAND, sizeof(csi), csi,
		    SSD_ELEM_NONE);
		return (CTL_RETVAL_ERROR);
	}

	list->segbytes = numbytes;
	list->segsectors = numbytes / dstblock;
	donebytes = 0;
	TAILQ_INIT(&run);
	list->tbdio = 0;
	while (donebytes < numbytes) {
		roundbytes = numbytes - donebytes;
		if (roundbytes > TPC_MAX_IO_SIZE) {
			roundbytes = TPC_MAX_IO_SIZE;
			roundbytes -= roundbytes % dstblock;
			if (pb > dstblock) {
				adj = (dstlba * dstblock + roundbytes - pbo) % pb;
				if (roundbytes > adj)
					roundbytes -= adj;
			}
		}

		tior = malloc(sizeof(*tior), M_CTL, M_WAITOK | M_ZERO);
		TAILQ_INIT(&tior->run);
		tior->buf = malloc(roundbytes, M_CTL, M_WAITOK);
		tior->list = list;
		TAILQ_INSERT_TAIL(&list->allio, tior, links);
		tior->io = tpcl_alloc_io();
		ctl_scsi_read_write(tior->io,
				    /*data_ptr*/ tior->buf,
				    /*data_len*/ roundbytes,
				    /*read_op*/ 1,
				    /*byte2*/ 0,
				    /*minimum_cdb_size*/ 0,
				    /*lba*/ srclba,
				    /*num_blocks*/ roundbytes / srcblock,
				    /*tag_type*/ CTL_TAG_SIMPLE,
				    /*control*/ 0);
		tior->io->io_hdr.retries = 3;
		tior->target = SSD_FORWARDED_SDS_EXSRC;
		tior->cscd = scscd;
		tior->lun = sl;
		tior->io->io_hdr.ctl_private[CTL_PRIV_FRONTEND].ptr = tior;

		tiow = malloc(sizeof(*tior), M_CTL, M_WAITOK | M_ZERO);
		TAILQ_INIT(&tiow->run);
		tiow->list = list;
		TAILQ_INSERT_TAIL(&list->allio, tiow, links);
		tiow->io = tpcl_alloc_io();
		ctl_scsi_read_write(tiow->io,
				    /*data_ptr*/ tior->buf,
				    /*data_len*/ roundbytes,
				    /*read_op*/ 0,
				    /*byte2*/ 0,
				    /*minimum_cdb_size*/ 0,
				    /*lba*/ dstlba,
				    /*num_blocks*/ roundbytes / dstblock,
				    /*tag_type*/ CTL_TAG_SIMPLE,
				    /*control*/ 0);
		tiow->io->io_hdr.retries = 3;
		tiow->target = SSD_FORWARDED_SDS_EXDST;
		tiow->cscd = dcscd;
		tiow->lun = dl;
		tiow->io->io_hdr.ctl_private[CTL_PRIV_FRONTEND].ptr = tiow;

		TAILQ_INSERT_TAIL(&tior->run, tiow, rlinks);
		TAILQ_INSERT_TAIL(&run, tior, rlinks);
		list->tbdio++;
		donebytes += roundbytes;
		srclba += roundbytes / srcblock;
		dstlba += roundbytes / dstblock;
	}

	while ((tior = TAILQ_FIRST(&run)) != NULL) {
		TAILQ_REMOVE(&run, tior, rlinks);
		if (tpcl_queue(tior->io, tior->lun) != CTL_RETVAL_COMPLETE)
			panic("tpcl_queue() error");
	}

	list->stage++;
	return (CTL_RETVAL_QUEUED);
}