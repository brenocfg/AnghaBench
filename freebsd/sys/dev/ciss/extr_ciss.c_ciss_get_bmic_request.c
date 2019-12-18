#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct ciss_softc {int dummy; } ;
struct ciss_request {size_t cr_length; struct ciss_command* cr_cc; int /*<<< orphan*/  cr_flags; void* cr_data; } ;
struct TYPE_8__ {int cdb_length; int /*<<< orphan*/ * cdb; scalar_t__ timeout; int /*<<< orphan*/  direction; int /*<<< orphan*/  attribute; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ target; scalar_t__ bus; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_1__ physical; } ;
struct TYPE_7__ {TYPE_2__ address; } ;
struct ciss_command {TYPE_4__ cdb; TYPE_3__ header; } ;
struct ciss_bmic_cdb {int bmic_opcode; int /*<<< orphan*/  size; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_ARRAY_CONTROLLER_READ ; 
 int /*<<< orphan*/  CISS_ARRAY_CONTROLLER_WRITE ; 
 int /*<<< orphan*/  CISS_CDB_ATTRIBUTE_SIMPLE ; 
 int /*<<< orphan*/  CISS_CDB_DIRECTION_READ ; 
 int /*<<< orphan*/  CISS_CDB_DIRECTION_WRITE ; 
 int /*<<< orphan*/  CISS_CDB_TYPE_COMMAND ; 
 int /*<<< orphan*/  CISS_HDR_ADDRESS_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  CISS_MALLOC_CLASS ; 
 int /*<<< orphan*/  CISS_REQ_DATAIN ; 
 int ENOMEM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bzero (struct ciss_bmic_cdb*,int) ; 
 int ciss_get_request (struct ciss_softc*,struct ciss_request**) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ciss_get_bmic_request(struct ciss_softc *sc, struct ciss_request **crp,
		      int opcode, void **bufp, size_t bufsize)
{
    struct ciss_request		*cr;
    struct ciss_command		*cc;
    struct ciss_bmic_cdb	*cbc;
    void			*buf;
    int				error;
    int				dataout;

    debug_called(2);

    cr = NULL;
    buf = NULL;

    /*
     * Get a request.
     */
    if ((error = ciss_get_request(sc, &cr)) != 0)
	goto out;

    /*
     * Allocate data storage if requested, determine the data direction.
     */
    dataout = 0;
    if ((bufsize > 0) && (bufp != NULL)) {
	if (*bufp == NULL) {
	    if ((buf = malloc(bufsize, CISS_MALLOC_CLASS, M_NOWAIT | M_ZERO)) == NULL) {
		error = ENOMEM;
		goto out;
	    }
	} else {
	    buf = *bufp;
	    dataout = 1;	/* we are given a buffer, so we are writing */
	}
    }

    /*
     * Build a CISS BMIC command to get the logical drive ID.
     */
    cr->cr_data = buf;
    cr->cr_length = bufsize;
    if (!dataout)
	cr->cr_flags = CISS_REQ_DATAIN;

    cc = cr->cr_cc;
    cc->header.address.physical.mode = CISS_HDR_ADDRESS_MODE_PERIPHERAL;
    cc->header.address.physical.bus = 0;
    cc->header.address.physical.target = 0;
    cc->cdb.cdb_length = sizeof(*cbc);
    cc->cdb.type = CISS_CDB_TYPE_COMMAND;
    cc->cdb.attribute = CISS_CDB_ATTRIBUTE_SIMPLE;
    cc->cdb.direction = dataout ? CISS_CDB_DIRECTION_WRITE : CISS_CDB_DIRECTION_READ;
    cc->cdb.timeout = 0;

    cbc = (struct ciss_bmic_cdb *)&(cc->cdb.cdb[0]);
    bzero(cbc, sizeof(*cbc));
    cbc->opcode = dataout ? CISS_ARRAY_CONTROLLER_WRITE : CISS_ARRAY_CONTROLLER_READ;
    cbc->bmic_opcode = opcode;
    cbc->size = htons((u_int16_t)bufsize);

out:
    if (error) {
	if (cr != NULL)
	    ciss_release_request(cr);
    } else {
	*crp = cr;
	if ((bufp != NULL) && (*bufp == NULL) && (buf != NULL))
	    *bufp = buf;
    }
    return(error);
}