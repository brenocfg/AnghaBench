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
typedef  int /*<<< orphan*/  u_int32_t ;
struct tws_softc {int /*<<< orphan*/  q_lock; TYPE_4__* reqs; scalar_t__ dma_mem_phys; TYPE_1__* sense_bufs; int /*<<< orphan*/  data_tag; scalar_t__ dma_mem; } ;
struct TYPE_6__ {int size_header; } ;
struct TYPE_7__ {TYPE_2__ header_desc; } ;
struct tws_command_packet {TYPE_3__ hdr; } ;
struct tws_command_header {int dummy; } ;
struct TYPE_8__ {int request_id; int /*<<< orphan*/  state; int /*<<< orphan*/  timeout; struct tws_command_packet* cmd_pkt; struct tws_softc* sc; scalar_t__ cmd_pkt_phy; int /*<<< orphan*/  dma_map; } ;
struct TYPE_5__ {scalar_t__ hdr_pkt_phy; TYPE_3__* hdr; } ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TWS_FREE_Q ; 
 int /*<<< orphan*/  TWS_REQ_STATE_FREE ; 
 int TWS_RESERVED_REQS ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct tws_command_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_q_insert_tail (struct tws_softc*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int tws_queue_depth ; 

__attribute__((used)) static int
tws_init_reqs(struct tws_softc *sc, u_int32_t dma_mem_size)
{

    struct tws_command_packet *cmd_buf;
    cmd_buf = (struct tws_command_packet *)sc->dma_mem;
    int i;

    bzero(cmd_buf, dma_mem_size);
    TWS_TRACE_DEBUG(sc, "phy cmd", sc->dma_mem_phys, 0);
    mtx_lock(&sc->q_lock);
    for ( i=0; i< tws_queue_depth; i++)
    {
        if (bus_dmamap_create(sc->data_tag, 0, &sc->reqs[i].dma_map)) {
            /* log a ENOMEM failure msg here */
            mtx_unlock(&sc->q_lock);
            return(FAILURE);
        } 
        sc->reqs[i].cmd_pkt =  &cmd_buf[i];

        sc->sense_bufs[i].hdr = &cmd_buf[i].hdr ;
        sc->sense_bufs[i].hdr_pkt_phy = sc->dma_mem_phys + 
                              (i * sizeof(struct tws_command_packet));

        sc->reqs[i].cmd_pkt_phy = sc->dma_mem_phys + 
                              sizeof(struct tws_command_header) +
                              (i * sizeof(struct tws_command_packet));
        sc->reqs[i].request_id = i;
        sc->reqs[i].sc = sc;

        sc->reqs[i].cmd_pkt->hdr.header_desc.size_header = 128;

	callout_init(&sc->reqs[i].timeout, 1);
        sc->reqs[i].state = TWS_REQ_STATE_FREE;
        if ( i >= TWS_RESERVED_REQS )
            tws_q_insert_tail(sc, &sc->reqs[i], TWS_FREE_Q);
    }
    mtx_unlock(&sc->q_lock);
    return(SUCCESS);
}