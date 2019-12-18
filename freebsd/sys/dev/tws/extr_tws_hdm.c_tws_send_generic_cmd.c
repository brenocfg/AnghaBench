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
typedef  int /*<<< orphan*/  u_int8_t ;
struct tws_softc {int dummy; } ;
struct tws_request {int /*<<< orphan*/  error_code; int /*<<< orphan*/  request_id; int /*<<< orphan*/  cb; TYPE_3__* cmd_pkt; } ;
struct tws_cmd_generic {int size; scalar_t__ count; scalar_t__ flags; scalar_t__ status; scalar_t__ host_id__unit; int /*<<< orphan*/  request_id; int /*<<< orphan*/  sgl_off__opcode; } ;
struct TYPE_4__ {struct tws_cmd_generic generic; } ;
struct TYPE_5__ {TYPE_1__ pkt_g; } ;
struct TYPE_6__ {TYPE_2__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_RES__OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TWS_REQ_TYPE_INTERNAL_CMD ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct tws_cmd_generic*,int) ; 
 int /*<<< orphan*/  tws_cmd_complete ; 
 struct tws_request* tws_get_request (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_submit_command (struct tws_softc*,struct tws_request*) ; 

int
tws_send_generic_cmd(struct tws_softc *sc, u_int8_t opcode)
{
    struct tws_request *req;
    struct tws_cmd_generic *cmd;

    TWS_TRACE_DEBUG(sc, "entry", sc, opcode);
    req = tws_get_request(sc, TWS_REQ_TYPE_INTERNAL_CMD);

    if ( req == NULL ) {
        TWS_TRACE_DEBUG(sc, "no requests", 0, 0);
        return(FAILURE);
    }

    cmd = &(req->cmd_pkt->cmd.pkt_g.generic);
    bzero(cmd, sizeof(struct tws_cmd_generic));
    /* req->cmd_pkt->hdr.header_desc.size_header = 128; */
    req->cb = tws_cmd_complete;

    cmd->sgl_off__opcode = BUILD_RES__OPCODE(0, opcode);
    cmd->size = 2;
    cmd->request_id = req->request_id;
    cmd->host_id__unit = 0;
    cmd->status = 0;
    cmd->flags = 0;
    cmd->count = 0;

    req->error_code = tws_submit_command(sc, req);

    return(SUCCESS);

}