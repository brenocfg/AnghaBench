#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union ccb {int /*<<< orphan*/  ccb_h; } ;
struct cam_periph {TYPE_3__* path; TYPE_2__* softc; } ;
struct TYPE_7__ {int /*<<< orphan*/  action; struct cam_periph* periph; scalar_t__ flags; int /*<<< orphan*/  request_ccbs; } ;
typedef  TYPE_2__ probe_softc ;
typedef  int /*<<< orphan*/  cam_status ;
struct TYPE_9__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_8__ {TYPE_1__* bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  last_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_PROBE ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PROBE_INVALID ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_periph_acquire (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_freeze_after_event (struct cam_periph*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ periph_links ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  probeschedule (struct cam_periph*) ; 
 int /*<<< orphan*/  scsi_delay ; 
 int /*<<< orphan*/  scsi_devise_transport (TYPE_3__*) ; 

__attribute__((used)) static cam_status
proberegister(struct cam_periph *periph, void *arg)
{
	union ccb *request_ccb;	/* CCB representing the probe request */
	probe_softc *softc;

	request_ccb = (union ccb *)arg;
	if (request_ccb == NULL) {
		printf("proberegister: no probe CCB, "
		       "can't register device\n");
		return(CAM_REQ_CMP_ERR);
	}

	softc = (probe_softc *)malloc(sizeof(*softc), M_CAMXPT, M_NOWAIT);

	if (softc == NULL) {
		printf("proberegister: Unable to probe new device. "
		       "Unable to allocate softc\n");
		return(CAM_REQ_CMP_ERR);
	}
	TAILQ_INIT(&softc->request_ccbs);
	TAILQ_INSERT_TAIL(&softc->request_ccbs, &request_ccb->ccb_h,
			  periph_links.tqe);
	softc->flags = 0;
	periph->softc = softc;
	softc->periph = periph;
	softc->action = PROBE_INVALID;
	if (cam_periph_acquire(periph) != 0)
		return (CAM_REQ_CMP_ERR);

	CAM_DEBUG(periph->path, CAM_DEBUG_PROBE, ("Probe started\n"));
	scsi_devise_transport(periph->path);

	/*
	 * Ensure we've waited at least a bus settle
	 * delay before attempting to probe the device.
	 * For HBAs that don't do bus resets, this won't make a difference.
	 */
	cam_periph_freeze_after_event(periph, &periph->path->bus->last_reset,
				      scsi_delay);
	probeschedule(periph);
	return(CAM_REQ_CMP);
}