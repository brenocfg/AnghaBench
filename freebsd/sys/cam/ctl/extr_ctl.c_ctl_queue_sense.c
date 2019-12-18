#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  targ_lun; } ;
struct TYPE_4__ {TYPE_3__ nexus; } ;
union ctl_io {TYPE_2__ scsiio; TYPE_1__ io_hdr; } ;
typedef  size_t uint32_t ;
struct scsi_sense_data {int dummy; } ;
struct ctl_softc {int /*<<< orphan*/  ctl_lock; struct ctl_lun** ctl_luns; } ;
struct ctl_port {int dummy; } ;
struct ctl_lun {int /*<<< orphan*/  lun_lock; struct scsi_sense_data** pending_sense; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 size_t CTL_MAX_INIT_PER_PORT ; 
 struct ctl_port* CTL_PORT (union ctl_io*) ; 
 int CTL_RETVAL_COMPLETE ; 
 struct ctl_softc* CTL_SOFTC (union ctl_io*) ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ctl_free_io (union ctl_io*) ; 
 size_t ctl_get_initindex (TYPE_3__*) ; 
 size_t ctl_lun_map_from_port (struct ctl_port*,int /*<<< orphan*/ ) ; 
 size_t ctl_max_luns ; 
 struct scsi_sense_data* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct scsi_sense_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct scsi_sense_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
ctl_queue_sense(union ctl_io *io)
{
	struct ctl_softc *softc = CTL_SOFTC(io);
	struct ctl_port *port = CTL_PORT(io);
	struct ctl_lun *lun;
	struct scsi_sense_data *ps;
	uint32_t initidx, p, targ_lun;

	CTL_DEBUG_PRINT(("ctl_queue_sense\n"));

	targ_lun = ctl_lun_map_from_port(port, io->io_hdr.nexus.targ_lun);

	/*
	 * LUN lookup will likely move to the ctl_work_thread() once we
	 * have our new queueing infrastructure (that doesn't put things on
	 * a per-LUN queue initially).  That is so that we can handle
	 * things like an INQUIRY to a LUN that we don't have enabled.  We
	 * can't deal with that right now.
	 * If we don't have a LUN for this, just toss the sense information.
	 */
	mtx_lock(&softc->ctl_lock);
	if (targ_lun >= ctl_max_luns ||
	    (lun = softc->ctl_luns[targ_lun]) == NULL) {
		mtx_unlock(&softc->ctl_lock);
		goto bailout;
	}
	mtx_lock(&lun->lun_lock);
	mtx_unlock(&softc->ctl_lock);

	initidx = ctl_get_initindex(&io->io_hdr.nexus);
	p = initidx / CTL_MAX_INIT_PER_PORT;
	if (lun->pending_sense[p] == NULL) {
		lun->pending_sense[p] = malloc(sizeof(*ps) * CTL_MAX_INIT_PER_PORT,
		    M_CTL, M_NOWAIT | M_ZERO);
	}
	if ((ps = lun->pending_sense[p]) != NULL) {
		ps += initidx % CTL_MAX_INIT_PER_PORT;
		memset(ps, 0, sizeof(*ps));
		memcpy(ps, &io->scsiio.sense_data, io->scsiio.sense_len);
	}
	mtx_unlock(&lun->lun_lock);

bailout:
	ctl_free_io(io);
	return (CTL_RETVAL_COMPLETE);
}