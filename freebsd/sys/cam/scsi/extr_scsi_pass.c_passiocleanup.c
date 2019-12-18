#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * data_ptr; } ;
struct TYPE_14__ {int /*<<< orphan*/  buf; } ;
struct TYPE_13__ {int /*<<< orphan*/ * smp_response; int /*<<< orphan*/ * smp_request; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data_ptr; } ;
struct TYPE_11__ {int /*<<< orphan*/ * data_ptr; } ;
struct TYPE_10__ {int /*<<< orphan*/  matches; int /*<<< orphan*/  patterns; } ;
struct TYPE_9__ {int func_code; } ;
union ccb {TYPE_7__ nvmeio; TYPE_6__ cdai; TYPE_5__ smpio; TYPE_4__ ataio; TYPE_3__ csio; TYPE_2__ cdm; TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct pass_softc {int /*<<< orphan*/  pass_io_zone; } ;
struct pass_io_req {int num_bufs; int flags; scalar_t__ data_flags; int num_kern_segs; int /*<<< orphan*/ ** user_bufs; TYPE_8__* kern_segptr; TYPE_8__** kern_bufs; TYPE_8__* user_segptr; union ccb ccb; } ;
struct TYPE_16__ {scalar_t__ ds_addr; } ;

/* Variables and functions */
 scalar_t__ CAM_DATA_PADDR ; 
 scalar_t__ CAM_DATA_SG ; 
 scalar_t__ CAM_DATA_VADDR ; 
 int CAM_PERIPH_MAXMAPS ; 
 int /*<<< orphan*/  M_SCSIPASS ; 
 int PASS_IO_KERN_SEG_MALLOC ; 
 int PASS_IO_USER_SEG_MALLOC ; 
#define  XPT_ATA_IO 135 
#define  XPT_CONT_TARGET_IO 134 
#define  XPT_DEV_ADVINFO 133 
#define  XPT_DEV_MATCH 132 
#define  XPT_NVME_ADMIN 131 
#define  XPT_NVME_IO 130 
#define  XPT_SCSI_IO 129 
#define  XPT_SMP_IO 128 
 int /*<<< orphan*/  free (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
passiocleanup(struct pass_softc *softc, struct pass_io_req *io_req)
{
	union ccb *ccb;
	u_int8_t **data_ptrs[CAM_PERIPH_MAXMAPS];
	int i, numbufs;

	ccb = &io_req->ccb;

	switch (ccb->ccb_h.func_code) {
	case XPT_DEV_MATCH:
		numbufs = min(io_req->num_bufs, 2);

		if (numbufs == 1) {
			data_ptrs[0] = (u_int8_t **)&ccb->cdm.matches;
		} else {
			data_ptrs[0] = (u_int8_t **)&ccb->cdm.patterns;
			data_ptrs[1] = (u_int8_t **)&ccb->cdm.matches;
		}
		break;
	case XPT_SCSI_IO:
	case XPT_CONT_TARGET_IO:
		data_ptrs[0] = &ccb->csio.data_ptr;
		numbufs = min(io_req->num_bufs, 1);
		break;
	case XPT_ATA_IO:
		data_ptrs[0] = &ccb->ataio.data_ptr;
		numbufs = min(io_req->num_bufs, 1);
		break;
	case XPT_SMP_IO:
		numbufs = min(io_req->num_bufs, 2);
		data_ptrs[0] = &ccb->smpio.smp_request;
		data_ptrs[1] = &ccb->smpio.smp_response;
		break;
	case XPT_DEV_ADVINFO:
		numbufs = min(io_req->num_bufs, 1);
		data_ptrs[0] = (uint8_t **)&ccb->cdai.buf;
		break;
	case XPT_NVME_IO:
	case XPT_NVME_ADMIN:
		data_ptrs[0] = &ccb->nvmeio.data_ptr;
		numbufs = min(io_req->num_bufs, 1);
		break;
	default:
		/* allow ourselves to be swapped once again */
		return;
		break; /* NOTREACHED */ 
	}

	if (io_req->flags & PASS_IO_USER_SEG_MALLOC) {
		free(io_req->user_segptr, M_SCSIPASS);
		io_req->user_segptr = NULL;
	}

	/*
	 * We only want to free memory we malloced.
	 */
	if (io_req->data_flags == CAM_DATA_VADDR) {
		for (i = 0; i < io_req->num_bufs; i++) {
			if (io_req->kern_bufs[i] == NULL)
				continue;

			free(io_req->kern_bufs[i], M_SCSIPASS);
			io_req->kern_bufs[i] = NULL;
		}
	} else if (io_req->data_flags == CAM_DATA_SG) {
		for (i = 0; i < io_req->num_kern_segs; i++) {
			if ((uint8_t *)(uintptr_t)
			    io_req->kern_segptr[i].ds_addr == NULL)
				continue;

			uma_zfree(softc->pass_io_zone, (uint8_t *)(uintptr_t)
			    io_req->kern_segptr[i].ds_addr);
			io_req->kern_segptr[i].ds_addr = 0;
		}
	}

	if (io_req->flags & PASS_IO_KERN_SEG_MALLOC) {
		free(io_req->kern_segptr, M_SCSIPASS);
		io_req->kern_segptr = NULL;
	}

	if (io_req->data_flags != CAM_DATA_PADDR) {
		for (i = 0; i < numbufs; i++) {
			/*
			 * Restore the user's buffer pointers to their
			 * previous values.
			 */
			if (io_req->user_bufs[i] != NULL)
				*data_ptrs[i] = io_req->user_bufs[i];
		}
	}

}