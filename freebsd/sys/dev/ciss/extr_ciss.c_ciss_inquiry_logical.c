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
struct scsi_inquiry {int /*<<< orphan*/  length; int /*<<< orphan*/  page_code; int /*<<< orphan*/  byte2; int /*<<< orphan*/  opcode; } ;
struct ciss_softc {int dummy; } ;
struct ciss_request {int cr_length; int /*<<< orphan*/  cr_flags; int /*<<< orphan*/ * cr_data; struct ciss_command* cr_cc; } ;
struct ciss_ldrive {int /*<<< orphan*/  cl_address; int /*<<< orphan*/  cl_geometry; } ;
struct TYPE_4__ {int cdb_length; int timeout; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  direction; int /*<<< orphan*/  attribute; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
struct ciss_command {TYPE_2__ cdb; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_CDB_ATTRIBUTE_SIMPLE ; 
 int /*<<< orphan*/  CISS_CDB_DIRECTION_READ ; 
 int /*<<< orphan*/  CISS_CDB_TYPE_COMMAND ; 
#define  CISS_CMD_STATUS_DATA_OVERRUN 130 
#define  CISS_CMD_STATUS_DATA_UNDERRUN 129 
#define  CISS_CMD_STATUS_SUCCESS 128 
 int /*<<< orphan*/  CISS_REQ_DATAIN ; 
 int /*<<< orphan*/  CISS_VPD_LOGICAL_DRIVE_GEOMETRY ; 
 int /*<<< orphan*/  INQUIRY ; 
 int /*<<< orphan*/  SI_EVPD ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int ciss_get_request (struct ciss_softc*,struct ciss_request**) ; 
 int ciss_name_command_status (int) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,...) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_report_request (struct ciss_request*,int*,int /*<<< orphan*/ *) ; 
 int ciss_synch_request (struct ciss_request*,int) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ciss_inquiry_logical(struct ciss_softc *sc, struct ciss_ldrive *ld)
{
    struct ciss_request			*cr;
    struct ciss_command			*cc;
    struct scsi_inquiry			*inq;
    int					error;
    int					command_status;

    cr = NULL;

    bzero(&ld->cl_geometry, sizeof(ld->cl_geometry));

    if ((error = ciss_get_request(sc, &cr)) != 0)
	goto out;

    cc = cr->cr_cc;
    cr->cr_data = &ld->cl_geometry;
    cr->cr_length = sizeof(ld->cl_geometry);
    cr->cr_flags = CISS_REQ_DATAIN;

    cc->header.address = ld->cl_address;
    cc->cdb.cdb_length = 6;
    cc->cdb.type = CISS_CDB_TYPE_COMMAND;
    cc->cdb.attribute = CISS_CDB_ATTRIBUTE_SIMPLE;
    cc->cdb.direction = CISS_CDB_DIRECTION_READ;
    cc->cdb.timeout = 30;

    inq = (struct scsi_inquiry *)&(cc->cdb.cdb[0]);
    inq->opcode = INQUIRY;
    inq->byte2 = SI_EVPD;
    inq->page_code = CISS_VPD_LOGICAL_DRIVE_GEOMETRY;
    scsi_ulto2b(sizeof(ld->cl_geometry), inq->length);

    if ((error = ciss_synch_request(cr, 60 * 1000)) != 0) {
	ciss_printf(sc, "error getting geometry (%d)\n", error);
	goto out;
    }

    ciss_report_request(cr, &command_status, NULL);
    switch(command_status) {
    case CISS_CMD_STATUS_SUCCESS:
    case CISS_CMD_STATUS_DATA_UNDERRUN:
	break;
    case CISS_CMD_STATUS_DATA_OVERRUN:
	ciss_printf(sc, "WARNING: Data overrun\n");
	break;
    default:
	ciss_printf(sc, "Error detecting logical drive geometry (%s)\n",
		    ciss_name_command_status(command_status));
	break;
    }

out:
    if (cr != NULL)
	ciss_release_request(cr);
    return(error);
}