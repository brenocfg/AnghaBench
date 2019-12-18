#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union ccb {int /*<<< orphan*/  ccb_h; } ;
struct cam_periph {int /*<<< orphan*/  path; TYPE_1__* softc; } ;
struct TYPE_3__ {int /*<<< orphan*/  action; struct cam_periph* periph; scalar_t__ flags; int /*<<< orphan*/  request_ccbs; } ;
typedef  TYPE_1__ probe_softc ;
typedef  int /*<<< orphan*/  cam_status ;
struct TYPE_4__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_PROBE ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PROBE_INVALID ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_device_transport (int /*<<< orphan*/ ) ; 
 scalar_t__ cam_periph_acquire (struct cam_periph*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ periph_links ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  probeschedule (struct cam_periph*) ; 

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

	softc = (probe_softc *)malloc(sizeof(*softc), M_CAMXPT, M_ZERO | M_NOWAIT);

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
	ata_device_transport(periph->path);
	probeschedule(periph);
	return(CAM_REQ_CMP);
}