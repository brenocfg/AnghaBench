#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ciss_softc {scalar_t__ ciss_perf; int /*<<< orphan*/  ciss_buffer_dmat; } ;
struct ciss_request {int cr_flags; int /*<<< orphan*/  cr_ccphys; int /*<<< orphan*/  cr_sg_tag; int /*<<< orphan*/  cr_datamap; struct ciss_command* cr_cc; struct ciss_softc* cr_sc; } ;
struct TYPE_6__ {int sg_in_list; int sg_total; } ;
struct ciss_command {TYPE_2__ header; TYPE_1__* sg; } ;
struct TYPE_7__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;
struct TYPE_5__ {scalar_t__ extension; int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CISS_REQ_BUSY ; 
 int CISS_REQ_DATAIN ; 
 int CISS_REQ_DATAOUT ; 
 int /*<<< orphan*/  CISS_SG_1 ; 
 int /*<<< orphan*/  CISS_SG_16 ; 
 int /*<<< orphan*/  CISS_SG_2 ; 
 int /*<<< orphan*/  CISS_SG_32 ; 
 int /*<<< orphan*/  CISS_SG_4 ; 
 int /*<<< orphan*/  CISS_SG_8 ; 
 int /*<<< orphan*/  CISS_SG_MAX ; 
 int /*<<< orphan*/  CISS_SG_NONE ; 
 int /*<<< orphan*/  CISS_TL_PERF_POST_CMD (struct ciss_softc*,struct ciss_request*) ; 
 int /*<<< orphan*/  CISS_TL_SIMPLE_POST_CMD (struct ciss_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
ciss_request_map_helper(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
    struct ciss_command	*cc;
    struct ciss_request *cr;
    struct ciss_softc	*sc;
    int			i;

    debug_called(2);

    cr = (struct ciss_request *)arg;
    sc = cr->cr_sc;
    cc = cr->cr_cc;

    for (i = 0; i < nseg; i++) {
	cc->sg[i].address = segs[i].ds_addr;
	cc->sg[i].length = segs[i].ds_len;
	cc->sg[i].extension = 0;
    }
    /* we leave the s/g table entirely within the command */
    cc->header.sg_in_list = nseg;
    cc->header.sg_total = nseg;

    if (cr->cr_flags & CISS_REQ_DATAIN)
	bus_dmamap_sync(sc->ciss_buffer_dmat, cr->cr_datamap, BUS_DMASYNC_PREREAD);
    if (cr->cr_flags & CISS_REQ_DATAOUT)
	bus_dmamap_sync(sc->ciss_buffer_dmat, cr->cr_datamap, BUS_DMASYNC_PREWRITE);

    if (nseg == 0)
	cr->cr_sg_tag = CISS_SG_NONE;
    else if (nseg == 1)
	cr->cr_sg_tag = CISS_SG_1;
    else if (nseg == 2)
	cr->cr_sg_tag = CISS_SG_2;
    else if (nseg <= 4)
	cr->cr_sg_tag = CISS_SG_4;
    else if (nseg <= 8)
	cr->cr_sg_tag = CISS_SG_8;
    else if (nseg <= 16)
	cr->cr_sg_tag = CISS_SG_16;
    else if (nseg <= 32)
	cr->cr_sg_tag = CISS_SG_32;
    else
	cr->cr_sg_tag = CISS_SG_MAX;

    /*
     * Post the command to the adapter.
     */
    cr->cr_flags |= CISS_REQ_BUSY;
    if (sc->ciss_perf)
	CISS_TL_PERF_POST_CMD(sc, cr);
    else
	CISS_TL_SIMPLE_POST_CMD(sc, cr->cr_ccphys);
}