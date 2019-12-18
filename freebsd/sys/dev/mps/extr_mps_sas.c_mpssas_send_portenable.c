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
struct mps_softc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  RequestFlags; } ;
struct TYPE_5__ {TYPE_1__ Default; } ;
struct mps_command {int /*<<< orphan*/  cm_complete; scalar_t__ cm_req; int /*<<< orphan*/ * cm_sge; int /*<<< orphan*/ * cm_data; TYPE_2__ cm_desc; } ;
struct TYPE_6__ {scalar_t__ VP_ID; scalar_t__ MsgFlags; int /*<<< orphan*/  Function; } ;
typedef  TYPE_3__ MPI2_PORT_ENABLE_REQUEST ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MPI2_FUNCTION_PORT_ENABLE ; 
 int /*<<< orphan*/  MPI2_REQ_DESCRIPT_FLAGS_DEFAULT_TYPE ; 
 int /*<<< orphan*/  MPS_FUNCTRACE (struct mps_softc*) ; 
 int /*<<< orphan*/  MPS_XINFO ; 
 struct mps_command* mps_alloc_command (struct mps_softc*) ; 
 int /*<<< orphan*/  mps_dprint (struct mps_softc*,int /*<<< orphan*/ ,char*,struct mps_command*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_map_command (struct mps_softc*,struct mps_command*) ; 
 int /*<<< orphan*/  mpssas_portenable_complete ; 

__attribute__((used)) static int
mpssas_send_portenable(struct mps_softc *sc)
{
	MPI2_PORT_ENABLE_REQUEST *request;
	struct mps_command *cm;

	MPS_FUNCTRACE(sc);

	if ((cm = mps_alloc_command(sc)) == NULL)
		return (EBUSY);
	request = (MPI2_PORT_ENABLE_REQUEST *)cm->cm_req;
	request->Function = MPI2_FUNCTION_PORT_ENABLE;
	request->MsgFlags = 0;
	request->VP_ID = 0;
	cm->cm_desc.Default.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_DEFAULT_TYPE;
	cm->cm_complete = mpssas_portenable_complete;
	cm->cm_data = NULL;
	cm->cm_sge = NULL;

	mps_map_command(sc, cm);
	mps_dprint(sc, MPS_XINFO, 
	    "mps_send_portenable finished cm %p req %p complete %p\n",
	    cm, cm->cm_req, cm->cm_complete);
	return (0);
}