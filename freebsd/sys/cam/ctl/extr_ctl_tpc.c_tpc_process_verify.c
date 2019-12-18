#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tpc_list {size_t curseg; int stage; int tbdio; int /*<<< orphan*/  allio; int /*<<< orphan*/  ctsio; scalar_t__* seg; scalar_t__ error; scalar_t__ abort; } ;
struct tpc_io {scalar_t__ lun; TYPE_3__* io; int /*<<< orphan*/  cscd; int /*<<< orphan*/  target; struct tpc_list* list; int /*<<< orphan*/  run; } ;
struct scsi_ec_segment_verify {int tur; int /*<<< orphan*/  src_cscd; } ;
typedef  int /*<<< orphan*/  csi ;
struct TYPE_8__ {int retries; TYPE_1__* ctl_private; } ;
struct TYPE_9__ {TYPE_2__ io_hdr; } ;
struct TYPE_7__ {struct tpc_io* ptr; } ;

/* Variables and functions */
 size_t CTL_PRIV_FRONTEND ; 
 int CTL_RETVAL_COMPLETE ; 
 int CTL_RETVAL_ERROR ; 
 int CTL_RETVAL_QUEUED ; 
 int /*<<< orphan*/  CTL_TAG_SIMPLE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SSD_ELEM_COMMAND ; 
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_FORWARDED_SDS_EXSRC ; 
 int /*<<< orphan*/  SSD_KEY_COPY_ABORTED ; 
 struct tpc_io* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct tpc_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tpc_io*,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  ctl_free_io (TYPE_3__*) ; 
 int /*<<< orphan*/  ctl_scsi_tur (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_sense (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_task_aborted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tpc_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 struct tpc_io* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  scsi_2btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ tpc_resolve (struct tpc_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpc_set_io_error_sense (struct tpc_list*) ; 
 TYPE_3__* tpcl_alloc_io () ; 
 int tpcl_queue (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static int
tpc_process_verify(struct tpc_list *list)
{
	struct scsi_ec_segment_verify *seg;
	struct tpc_io *tio;
	uint64_t sl;
	uint16_t cscd;
	uint8_t csi[4];

	scsi_ulto4b(list->curseg, csi);
	if (list->stage == 1) {
		while ((tio = TAILQ_FIRST(&list->allio)) != NULL) {
			TAILQ_REMOVE(&list->allio, tio, links);
			ctl_free_io(tio->io);
			free(tio, M_CTL);
		}
		if (list->abort) {
			ctl_set_task_aborted(list->ctsio);
			return (CTL_RETVAL_ERROR);
		} else if (list->error) {
			tpc_set_io_error_sense(list);
			return (CTL_RETVAL_ERROR);
		} else
			return (CTL_RETVAL_COMPLETE);
	}

	TAILQ_INIT(&list->allio);
	seg = (struct scsi_ec_segment_verify *)list->seg[list->curseg];
	cscd = scsi_2btoul(seg->src_cscd);
	sl = tpc_resolve(list, cscd, NULL, NULL, NULL);
	if (sl == UINT64_MAX) {
		ctl_set_sense(list->ctsio, /*current_error*/ 1,
		    /*sense_key*/ SSD_KEY_COPY_ABORTED,
		    /*asc*/ 0x08, /*ascq*/ 0x04,
		    SSD_ELEM_COMMAND, sizeof(csi), csi,
		    SSD_ELEM_NONE);
		return (CTL_RETVAL_ERROR);
	}

//	printf("Verify %ju\n", sl);

	if ((seg->tur & 0x01) == 0)
		return (CTL_RETVAL_COMPLETE);

	list->tbdio = 1;
	tio = malloc(sizeof(*tio), M_CTL, M_WAITOK | M_ZERO);
	TAILQ_INIT(&tio->run);
	tio->list = list;
	TAILQ_INSERT_TAIL(&list->allio, tio, links);
	tio->io = tpcl_alloc_io();
	ctl_scsi_tur(tio->io, /*tag_type*/ CTL_TAG_SIMPLE, /*control*/ 0);
	tio->io->io_hdr.retries = 3;
	tio->target = SSD_FORWARDED_SDS_EXSRC;
	tio->cscd = cscd;
	tio->lun = sl;
	tio->io->io_hdr.ctl_private[CTL_PRIV_FRONTEND].ptr = tio;
	list->stage++;
	if (tpcl_queue(tio->io, tio->lun) != CTL_RETVAL_COMPLETE)
		panic("tpcl_queue() error");
	return (CTL_RETVAL_QUEUED);
}