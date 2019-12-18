#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int16_t ;
struct tws_softc {scalar_t__ is64bit; int /*<<< orphan*/  data_tag; } ;
struct tws_request {int error_code; int flags; scalar_t__ type; struct tws_softc* sc; TYPE_6__* cmd_pkt; int /*<<< orphan*/  dma_map; TYPE_2__* ccb_ptr; } ;
struct tws_cmd_generic {int size; } ;
typedef  scalar_t__ gcmd ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
struct TYPE_10__ {int lun_h4__sgl_entries; int /*<<< orphan*/  sg_list; int /*<<< orphan*/  res__opcode; } ;
struct TYPE_9__ {struct tws_cmd_generic generic; } ;
struct TYPE_11__ {TYPE_4__ pkt_a; TYPE_3__ pkt_g; } ;
struct TYPE_12__ {TYPE_5__ cmd; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
struct TYPE_8__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CAM_REQ_TOO_BIG ; 
 int EFBIG ; 
 scalar_t__ GET_OPCODE (int /*<<< orphan*/ ) ; 
 int TWS_DIR_IN ; 
 int TWS_DIR_OUT ; 
 scalar_t__ TWS_FW_CMD_EXECUTE_SCSI ; 
 scalar_t__ TWS_REQ_TYPE_GETSET_PARAM ; 
 scalar_t__ TWS_REQ_TYPE_PASSTHRU ; 
 int /*<<< orphan*/  TWS_TRACE (struct tws_softc*,char*,int,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_fill_sg_list (struct tws_softc*,void*,void*,int) ; 
 int tws_submit_command (struct tws_softc*,struct tws_request*) ; 
 int /*<<< orphan*/  tws_use_32bit_sgls ; 

__attribute__((used)) static void
tws_dmamap_data_load_cbfn(void *arg, bus_dma_segment_t *segs, 
                            int nseg, int error)
{
    struct tws_request *req = (struct tws_request *)arg;
    struct tws_softc *sc = req->sc;
    u_int16_t sgls = nseg;
    void *sgl_ptr;
    struct tws_cmd_generic *gcmd;


    if ( error ) {
        TWS_TRACE(sc, "SOMETHING BAD HAPPENED! error = %d\n", error, 0);
    }

    if ( error == EFBIG ) {
        TWS_TRACE(sc, "not enough data segs", 0, nseg);
        req->error_code = error;
        req->ccb_ptr->ccb_h.status = CAM_REQ_TOO_BIG;
        return;
    }

    if ( req->flags & TWS_DIR_IN )
        bus_dmamap_sync(req->sc->data_tag, req->dma_map, 
                                            BUS_DMASYNC_PREREAD);
    if ( req->flags & TWS_DIR_OUT )
        bus_dmamap_sync(req->sc->data_tag, req->dma_map, 
                                        BUS_DMASYNC_PREWRITE);
    if ( segs ) {
        if ( (req->type == TWS_REQ_TYPE_PASSTHRU && 
             GET_OPCODE(req->cmd_pkt->cmd.pkt_a.res__opcode) != 
                            TWS_FW_CMD_EXECUTE_SCSI) ||
              req->type == TWS_REQ_TYPE_GETSET_PARAM) {
            gcmd = &req->cmd_pkt->cmd.pkt_g.generic;
            sgl_ptr = (u_int32_t *)(gcmd) + gcmd->size;
            gcmd->size += sgls * 
                          ((req->sc->is64bit && !tws_use_32bit_sgls) ? 4 : 2 );
            tws_fill_sg_list(req->sc, (void *)segs, sgl_ptr, sgls);

        } else {
            tws_fill_sg_list(req->sc, (void *)segs, 
                      (void *)&(req->cmd_pkt->cmd.pkt_a.sg_list), sgls);
            req->cmd_pkt->cmd.pkt_a.lun_h4__sgl_entries |= sgls ;
        }
    }


    req->error_code = tws_submit_command(req->sc, req);

}