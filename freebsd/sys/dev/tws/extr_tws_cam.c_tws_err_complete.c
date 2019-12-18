#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int64_t ;
typedef  int u_int32_t ;
typedef  size_t u_int16_t ;
struct tws_softc {int obfl_q_overrun; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  tws_dev; struct tws_request* reqs; } ;
struct tws_sense {struct tws_command_header* hdr; } ;
struct tws_request {size_t error_code; int type; } ;
struct TYPE_2__ {size_t request_id; int size_header; } ;
struct tws_command_header {TYPE_1__ header_desc; } ;

/* Variables and functions */
 int TWS_BIT13 ; 
 int /*<<< orphan*/  TWS_I2O0_HOBQPH ; 
 int /*<<< orphan*/  TWS_I2O0_HOBQPL ; 
 int /*<<< orphan*/  TWS_I2O0_STATUS ; 
 size_t TWS_REQ_RET_SUBMIT_SUCCESS ; 
#define  TWS_REQ_TYPE_GETSET_PARAM 130 
#define  TWS_REQ_TYPE_PASSTHRU 129 
#define  TWS_REQ_TYPE_SCSI_IO 128 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,...) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct tws_sense* tws_find_sense_from_mfa (struct tws_softc*,int) ; 
 int /*<<< orphan*/  tws_getset_param_complete (struct tws_request*) ; 
 int /*<<< orphan*/  tws_passthru_err_complete (struct tws_request*,struct tws_command_header*) ; 
 int tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tws_scsi_err_complete (struct tws_request*,struct tws_command_header*) ; 
 int /*<<< orphan*/  tws_write_reg (struct tws_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
tws_err_complete(struct tws_softc *sc, u_int64_t mfa)
{
    struct tws_command_header *hdr;
    struct tws_sense *sen;
    struct tws_request *req;
    u_int16_t req_id;
    u_int32_t reg, status;

    if ( !mfa ) {
        TWS_TRACE_DEBUG(sc, "null mfa", 0, mfa);
        return;
    } else {
        /* lookup the sense */
        sen = tws_find_sense_from_mfa(sc, mfa);
        if ( sen == NULL ) {
            TWS_TRACE_DEBUG(sc, "found null req", 0, mfa);
            return;
        }
        hdr = sen->hdr;
        TWS_TRACE_DEBUG(sc, "sen, hdr", sen, hdr);
        req_id = hdr->header_desc.request_id;
        req = &sc->reqs[req_id];
        TWS_TRACE_DEBUG(sc, "req, id", req, req_id);
        if ( req->error_code != TWS_REQ_RET_SUBMIT_SUCCESS )
            TWS_TRACE_DEBUG(sc, "submit failure?", 0, req->error_code);
    }

    switch (req->type) {
        case TWS_REQ_TYPE_PASSTHRU :
            tws_passthru_err_complete(req, hdr);
            break;
        case TWS_REQ_TYPE_GETSET_PARAM :
            tws_getset_param_complete(req);
            break;
        case TWS_REQ_TYPE_SCSI_IO :
            tws_scsi_err_complete(req, hdr);
            break;
            
    }

    mtx_lock(&sc->io_lock);
    hdr->header_desc.size_header = 128;
    reg = (u_int32_t)( mfa>>32);
    tws_write_reg(sc, TWS_I2O0_HOBQPH, reg, 4);
    reg = (u_int32_t)(mfa);
    tws_write_reg(sc, TWS_I2O0_HOBQPL, reg, 4);

    status = tws_read_reg(sc, TWS_I2O0_STATUS, 4);
    if ( status & TWS_BIT13 ) {
        device_printf(sc->tws_dev,  "OBFL Overrun\n");
        sc->obfl_q_overrun = true;
    }
    mtx_unlock(&sc->io_lock);
}