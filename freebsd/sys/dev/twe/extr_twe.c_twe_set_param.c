#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct twe_softc {int dummy; } ;
struct twe_request {int tr_flags; int /*<<< orphan*/  tr_length; TYPE_2__* tr_data; } ;
struct TYPE_6__ {int size; int param_count; scalar_t__ unit; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {TYPE_1__ param; } ;
struct TYPE_7__ {int table_id; int parameter_id; int parameter_size_bytes; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ TWE_Param ;
typedef  TYPE_3__ TWE_Command ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int TWE_CMD_DATAIN ; 
 int TWE_CMD_DATAOUT ; 
 TYPE_3__* TWE_FIND_COMMAND (struct twe_request*) ; 
 int /*<<< orphan*/  TWE_IO_ASSERT_LOCKED (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_OP_SET_PARAM ; 
 int /*<<< orphan*/  TWE_SECTOR_SIZE ; 
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ twe_get_request (struct twe_softc*,struct twe_request**) ; 
 int twe_immediate_request (struct twe_request*,int) ; 
 int /*<<< orphan*/  twe_release_request (struct twe_request*) ; 
 scalar_t__ twe_report_request (struct twe_request*) ; 

__attribute__((used)) static int
twe_set_param(struct twe_softc *sc, int table_id, int param_id, int param_size, void *data)
{
    struct twe_request	*tr;
    TWE_Command		*cmd;
    TWE_Param		*param;
    int			error;

    debug_called(4);

    TWE_IO_ASSERT_LOCKED(sc);
    tr = NULL;
    param = NULL;
    error = ENOMEM;

    /* get a command */
    if (twe_get_request(sc, &tr))
	goto out;

    /* get a buffer */
    if ((param = (TWE_Param *)malloc(TWE_SECTOR_SIZE, M_DEVBUF, M_NOWAIT)) == NULL)
	goto out;
    tr->tr_data = param;
    tr->tr_length = TWE_SECTOR_SIZE;
    tr->tr_flags = TWE_CMD_DATAIN | TWE_CMD_DATAOUT;

    /* build the command for the controller */
    cmd = TWE_FIND_COMMAND(tr);
    cmd->param.opcode = TWE_OP_SET_PARAM;
    cmd->param.size = 2;
    cmd->param.unit = 0;
    cmd->param.param_count = 1;

    /* fill in the outbound parameter data */
    param->table_id = table_id;
    param->parameter_id = param_id;
    param->parameter_size_bytes = param_size;
    bcopy(data, param->data, param_size);

    /* XXX could use twe_wait_request here if interrupts were enabled? */
    error = twe_immediate_request(tr, 1 /* usetmp */);
    if (error == 0) {
	if (twe_report_request(tr))
	    error = EIO;
    }

out:
    if (tr != NULL)
	twe_release_request(tr);
    if (param != NULL)
	free(param, M_DEVBUF);
    return(error);
}