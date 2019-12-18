#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/ * kbuff_arr; int /*<<< orphan*/ * mfi_kbuff_arr_busaddr; int /*<<< orphan*/ * mfi_kbuff_arr_dmamap; int /*<<< orphan*/ * mfi_kbuff_arr_dmat; int /*<<< orphan*/  mfi_parent_dmat; } ;
struct mfi_sg64 {int dummy; } ;
struct mfi_sg32 {int dummy; } ;
struct mfi_ioc_packet {int mfi_sge_count; TYPE_7__* mfi_sgl; scalar_t__ mfi_sgl_off; } ;
struct mfi_command {int cm_extra_frames; int cm_total_frame_size; int /*<<< orphan*/  cm_flags; TYPE_6__* cm_frame; } ;
struct megasas_sge {int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  length; } ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_14__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_11__ {TYPE_3__* sg32; TYPE_2__* sg64; } ;
struct TYPE_12__ {TYPE_4__ sgl; } ;
struct TYPE_8__ {int sg_count; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {TYPE_5__ stp; TYPE_1__ header; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MFI_CMD_MAPPED ; 
 int /*<<< orphan*/  MFI_FRAME_SGL64 ; 
 int MFI_FRAME_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfi_addr_cb ; 

__attribute__((used)) static int
mfi_stp_cmd(struct mfi_softc *sc, struct mfi_command *cm,caddr_t arg)
{
	uint8_t i;
	struct mfi_ioc_packet *ioc;
	ioc = (struct mfi_ioc_packet *)arg;
	int sge_size, error;
	struct megasas_sge *kern_sge;

	memset(sc->kbuff_arr, 0, sizeof(sc->kbuff_arr));
	kern_sge =(struct megasas_sge *) ((uintptr_t)cm->cm_frame + ioc->mfi_sgl_off);
	cm->cm_frame->header.sg_count = ioc->mfi_sge_count;

	if (sizeof(bus_addr_t) == 8) {
		cm->cm_frame->header.flags |= MFI_FRAME_SGL64;
		cm->cm_extra_frames = 2;
		sge_size = sizeof(struct mfi_sg64);
	} else {
		cm->cm_extra_frames =  (cm->cm_total_frame_size - 1) / MFI_FRAME_SIZE;
		sge_size = sizeof(struct mfi_sg32);
	}

	cm->cm_total_frame_size += (sge_size * ioc->mfi_sge_count);
	for (i = 0; i < ioc->mfi_sge_count; i++) {
			if (bus_dma_tag_create( sc->mfi_parent_dmat,	/* parent */
			1, 0,			/* algnmnt, boundary */
			BUS_SPACE_MAXADDR_32BIT,/* lowaddr */
			BUS_SPACE_MAXADDR,	/* highaddr */
			NULL, NULL,		/* filter, filterarg */
			ioc->mfi_sgl[i].iov_len,/* maxsize */
			2,			/* nsegments */
			ioc->mfi_sgl[i].iov_len,/* maxsegsize */
			BUS_DMA_ALLOCNOW,	/* flags */
			NULL, NULL,		/* lockfunc, lockarg */
			&sc->mfi_kbuff_arr_dmat[i])) {
			device_printf(sc->mfi_dev,
			    "Cannot allocate mfi_kbuff_arr_dmat tag\n");
			return (ENOMEM);
		}

		if (bus_dmamem_alloc(sc->mfi_kbuff_arr_dmat[i],
		    (void **)&sc->kbuff_arr[i], BUS_DMA_NOWAIT,
		    &sc->mfi_kbuff_arr_dmamap[i])) {
			device_printf(sc->mfi_dev,
			    "Cannot allocate mfi_kbuff_arr_dmamap memory\n");
			return (ENOMEM);
		}

		bus_dmamap_load(sc->mfi_kbuff_arr_dmat[i],
		    sc->mfi_kbuff_arr_dmamap[i], sc->kbuff_arr[i],
		    ioc->mfi_sgl[i].iov_len, mfi_addr_cb,
		    &sc->mfi_kbuff_arr_busaddr[i], 0);

		if (!sc->kbuff_arr[i]) {
			device_printf(sc->mfi_dev,
			    "Could not allocate memory for kbuff_arr info\n");
			return -1;
		}
		kern_sge[i].phys_addr = sc->mfi_kbuff_arr_busaddr[i];
		kern_sge[i].length = ioc->mfi_sgl[i].iov_len;

		if (sizeof(bus_addr_t) == 8) {
			cm->cm_frame->stp.sgl.sg64[i].addr =
			    kern_sge[i].phys_addr;
			cm->cm_frame->stp.sgl.sg64[i].len =
			    ioc->mfi_sgl[i].iov_len;
		} else {
			cm->cm_frame->stp.sgl.sg32[i].addr =
			    kern_sge[i].phys_addr;
			cm->cm_frame->stp.sgl.sg32[i].len =
			    ioc->mfi_sgl[i].iov_len;
		}

		error = copyin(ioc->mfi_sgl[i].iov_base,
		    sc->kbuff_arr[i],
		    ioc->mfi_sgl[i].iov_len);
		if (error != 0) {
			device_printf(sc->mfi_dev, "Copy in failed\n");
			return error;
		}
	}

	cm->cm_flags |=MFI_CMD_MAPPED;
	return 0;
}