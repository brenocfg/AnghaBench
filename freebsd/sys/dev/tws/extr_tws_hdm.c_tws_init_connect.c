#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  scalar_t__ u_int16_t ;
struct TYPE_9__ {int /*<<< orphan*/  reqs_out; } ;
struct TYPE_8__ {scalar_t__ fw_on_ctlr_build; scalar_t__ fw_on_ctlr_branch; int /*<<< orphan*/  fw_on_ctlr_srl; scalar_t__ working_build; scalar_t__ working_branch; int /*<<< orphan*/  working_srl; } ;
struct tws_softc {TYPE_4__ stats; TYPE_3__ cinfo; scalar_t__ is64bit; struct tws_request* reqs; } ;
struct tws_request {size_t type; scalar_t__ request_id; int /*<<< orphan*/  state; int /*<<< orphan*/  error_code; TYPE_2__* cmd_pkt; int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * ccb_ptr; int /*<<< orphan*/ * cb; int /*<<< orphan*/  flags; scalar_t__ length; int /*<<< orphan*/ * data; } ;
struct tws_command_apache {int dummy; } ;
struct tws_cmd_init_connect {int size; scalar_t__ request_id; scalar_t__ fw_build; scalar_t__ fw_branch; int /*<<< orphan*/  fw_srl; scalar_t__ fw_arch_id; int /*<<< orphan*/  features; scalar_t__ message_credits; int /*<<< orphan*/  res1__opcode; } ;
struct TYPE_6__ {struct tws_cmd_init_connect init_connect; } ;
struct TYPE_10__ {TYPE_1__ pkt_g; } ;
struct TYPE_7__ {TYPE_5__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_RES__OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TWS_64BIT_SG_ADDRESSES ; 
 int /*<<< orphan*/  TWS_BIT_EXTEND ; 
 int /*<<< orphan*/  TWS_CURRENT_FW_SRL ; 
 int /*<<< orphan*/  TWS_DIR_UNKNOWN ; 
 int /*<<< orphan*/  TWS_FW_CMD_INIT_CONNECTION ; 
 scalar_t__ TWS_INVALID_REQID ; 
 int /*<<< orphan*/  TWS_REQ_RET_INVALID ; 
 int /*<<< orphan*/  TWS_REQ_STATE_BUSY ; 
 int /*<<< orphan*/  TWS_REQ_STATE_FREE ; 
 size_t TWS_REQ_TYPE_INTERNAL_CMD ; 
 int /*<<< orphan*/  TWS_TRACE (struct tws_softc*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct tws_request* tws_get_request (struct tws_softc*,size_t) ; 
 scalar_t__ tws_poll4_response (struct tws_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_submit_command (struct tws_softc*,struct tws_request*) ; 
 int /*<<< orphan*/  tws_swap16 (int) ; 
 int /*<<< orphan*/  tws_swap32 (int) ; 
 int /*<<< orphan*/  tws_swap64 (int) ; 
 int /*<<< orphan*/  tws_use_32bit_sgls ; 

int
tws_init_connect(struct tws_softc *sc, u_int16_t mcreadits )
{
    struct tws_request *req;
    struct tws_cmd_init_connect *initc;
    u_int16_t reqid;
    u_int64_t mfa;

    TWS_TRACE_DEBUG(sc, "entry", 0, mcreadits);
#if       0
    req = tws_get_request(sc, TWS_REQ_TYPE_INTERNAL_CMD);
#else  // 0
    req = &sc->reqs[TWS_REQ_TYPE_INTERNAL_CMD];
    bzero(&req->cmd_pkt->cmd, sizeof(struct tws_command_apache));
    req->data = NULL;
    req->length = 0;
    req->type = TWS_REQ_TYPE_INTERNAL_CMD;
    req->flags = TWS_DIR_UNKNOWN;
    req->error_code = TWS_REQ_RET_INVALID;
    req->cb = NULL;
    req->ccb_ptr = NULL;
    callout_stop(&req->timeout);
    req->next = req->prev = NULL;
    req->state = TWS_REQ_STATE_BUSY;
#endif // 0

    if ( req == NULL ) {
        TWS_TRACE_DEBUG(sc, "no requests", 0, 0);
//      device_printf(sc->tws_dev,  "No requests for initConnect\n");
        return(FAILURE);
    }

    tws_swap16(0xbeef); /* just for test */
    tws_swap32(0xdeadbeef); /* just for test */
    tws_swap64(0xdeadbeef); /* just for test */
    initc = &(req->cmd_pkt->cmd.pkt_g.init_connect);
    /* req->cmd_pkt->hdr.header_desc.size_header = 128; */

    initc->res1__opcode = 
              BUILD_RES__OPCODE(0, TWS_FW_CMD_INIT_CONNECTION);
    initc->size = 6;
    initc->request_id = req->request_id;
    initc->message_credits = mcreadits;
    initc->features |= TWS_BIT_EXTEND;
    if ( sc->is64bit && !tws_use_32bit_sgls )
        initc->features |= TWS_64BIT_SG_ADDRESSES;
    /* assuming set features is always on */ 

    initc->size = 6;
    initc->fw_srl = sc->cinfo.working_srl = TWS_CURRENT_FW_SRL;
    initc->fw_arch_id = 0;
    initc->fw_branch = sc->cinfo.working_branch = 0;
    initc->fw_build = sc->cinfo.working_build = 0;

    req->error_code = tws_submit_command(sc, req);
    reqid = tws_poll4_response(sc, &mfa);
    if ( reqid != TWS_INVALID_REQID && reqid == req->request_id ) {
        sc->cinfo.fw_on_ctlr_srl = initc->fw_srl;
        sc->cinfo.fw_on_ctlr_branch = initc->fw_branch;
        sc->cinfo.fw_on_ctlr_build = initc->fw_build;
        sc->stats.reqs_out++;
        req->state = TWS_REQ_STATE_FREE;
    }
    else {
        /*
         * REVISIT::If init connect fails we need to reset the ctlr
         * and try again? 
         */ 
        TWS_TRACE(sc, "unexpected req_id ", reqid, 0);
        TWS_TRACE(sc, "INITCONNECT FAILED", reqid, 0);
        return(FAILURE);
    }
    return(SUCCESS);
}