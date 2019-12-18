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
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  int /*<<< orphan*/  uint8_t ;
struct tpc_list {scalar_t__ service_action; int error; size_t curseg; size_t nseg; int flags; int completed; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; void* last_active; TYPE_1__* token; struct tpc_list* params; scalar_t__ stage; struct scsi_ec_segment** seg; struct ctl_scsiio* ctsio; struct ctl_lun* lun; } ;
struct scsi_ec_segment {int type_code; } ;
struct ctl_softc {int /*<<< orphan*/  tpc_lock; } ;
struct ctl_scsiio {int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; } ;
struct ctl_lun {int /*<<< orphan*/  lun_lock; int /*<<< orphan*/  tpc_lists; struct ctl_softc* ctl_softc; } ;
typedef  int /*<<< orphan*/  csi ;
struct TYPE_2__ {scalar_t__ active; void* last_active; } ;

/* Variables and functions */
 int CTL_RETVAL_COMPLETE ; 
 int CTL_RETVAL_ERROR ; 
 int CTL_RETVAL_QUEUED ; 
 int EC_LIST_ID_USAGE_MASK ; 
 int EC_LIST_ID_USAGE_NONE ; 
#define  EC_SEG_B2B 130 
#define  EC_SEG_REGISTER_KEY 129 
#define  EC_SEG_VERIFY 128 
 scalar_t__ EC_WUT ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  SSD_ELEM_COMMAND ; 
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_KEY_COPY_ABORTED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tpc_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_sense (struct ctl_scsiio*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 int /*<<< orphan*/  free (struct tpc_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_ulto4b (size_t,int /*<<< orphan*/ *) ; 
 void* time_uptime ; 
 int tpc_process_b2b (struct tpc_list*) ; 
 int tpc_process_register_key (struct tpc_list*) ; 
 int tpc_process_verify (struct tpc_list*) ; 
 int tpc_process_wut (struct tpc_list*) ; 
 int tpc_process_zero_wut (struct tpc_list*) ; 

__attribute__((used)) static void
tpc_process(struct tpc_list *list)
{
	struct ctl_lun *lun = list->lun;
	struct ctl_softc *softc = lun->ctl_softc;
	struct scsi_ec_segment *seg;
	struct ctl_scsiio *ctsio = list->ctsio;
	int retval = CTL_RETVAL_COMPLETE;
	uint8_t csi[4];

	if (list->service_action == EC_WUT) {
		if (list->token != NULL)
			retval = tpc_process_wut(list);
		else
			retval = tpc_process_zero_wut(list);
		if (retval == CTL_RETVAL_QUEUED)
			return;
		if (retval == CTL_RETVAL_ERROR) {
			list->error = 1;
			goto done;
		}
	} else {
//printf("ZZZ %d cscd, %d segs\n", list->ncscd, list->nseg);
		while (list->curseg < list->nseg) {
			seg = list->seg[list->curseg];
			switch (seg->type_code) {
			case EC_SEG_B2B:
				retval = tpc_process_b2b(list);
				break;
			case EC_SEG_VERIFY:
				retval = tpc_process_verify(list);
				break;
			case EC_SEG_REGISTER_KEY:
				retval = tpc_process_register_key(list);
				break;
			default:
				scsi_ulto4b(list->curseg, csi);
				ctl_set_sense(ctsio, /*current_error*/ 1,
				    /*sense_key*/ SSD_KEY_COPY_ABORTED,
				    /*asc*/ 0x26, /*ascq*/ 0x09,
				    SSD_ELEM_COMMAND, sizeof(csi), csi,
				    SSD_ELEM_NONE);
				goto done;
			}
			if (retval == CTL_RETVAL_QUEUED)
				return;
			if (retval == CTL_RETVAL_ERROR) {
				list->error = 1;
				goto done;
			}
			list->curseg++;
			list->stage = 0;
		}
	}

	ctl_set_success(ctsio);

done:
//printf("ZZZ done\n");
	free(list->params, M_CTL);
	list->params = NULL;
	if (list->token) {
		mtx_lock(&softc->tpc_lock);
		if (--list->token->active == 0)
			list->token->last_active = time_uptime;
		mtx_unlock(&softc->tpc_lock);
		list->token = NULL;
	}
	mtx_lock(&lun->lun_lock);
	if ((list->flags & EC_LIST_ID_USAGE_MASK) == EC_LIST_ID_USAGE_NONE) {
		TAILQ_REMOVE(&lun->tpc_lists, list, links);
		free(list, M_CTL);
	} else {
		list->completed = 1;
		list->last_active = time_uptime;
		list->sense_data = ctsio->sense_data;
		list->sense_len = ctsio->sense_len;
		list->scsi_status = ctsio->scsi_status;
	}
	mtx_unlock(&lun->lun_lock);

	ctl_done((union ctl_io *)ctsio);
}