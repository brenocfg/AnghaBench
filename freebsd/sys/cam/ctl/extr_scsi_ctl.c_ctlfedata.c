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
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int kern_sg_entries; size_t ext_data_filled; size_t kern_data_len; int /*<<< orphan*/ * kern_data_ptr; } ;
union ctl_io {TYPE_2__ io_hdr; TYPE_1__ scsiio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int u_int16_t ;
struct ctlfe_softc {size_t maxio; } ;
struct ctlfe_lun_softc {struct ctlfe_softc* parent_softc; } ;
struct ctlfe_cmd_info {int cur_transfer_index; size_t cur_transfer_off; int /*<<< orphan*/  flags; TYPE_3__* cam_sglist; } ;
struct ctl_sg_entry {size_t len; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  ccb_flags ;
struct TYPE_6__ {size_t ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DATA_MASK ; 
 int /*<<< orphan*/  CAM_DATA_PADDR ; 
 int /*<<< orphan*/  CAM_DATA_SG ; 
 int /*<<< orphan*/  CAM_DATA_SG_PADDR ; 
 int /*<<< orphan*/  CAM_DATA_VADDR ; 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  CAM_DIR_MASK ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  CTLFE_CMD_PIECEWISE ; 
 int CTLFE_MAX_SEGS ; 
 int CTL_FLAG_BUS_ADDR ; 
 int CTL_FLAG_DATA_IN ; 
 int CTL_FLAG_DATA_MASK ; 
 struct ctlfe_cmd_info* PRIV_INFO (union ctl_io*) ; 

__attribute__((used)) static void
ctlfedata(struct ctlfe_lun_softc *softc, union ctl_io *io,
    ccb_flags *flags, uint8_t **data_ptr, uint32_t *dxfer_len,
    u_int16_t *sglist_cnt)
{
	struct ctlfe_softc *bus_softc;
	struct ctlfe_cmd_info *cmd_info;
	struct ctl_sg_entry *ctl_sglist;
	bus_dma_segment_t *cam_sglist;
	size_t off;
	int i, idx;

	cmd_info = PRIV_INFO(io);
	bus_softc = softc->parent_softc;

	/*
	 * Set the direction, relative to the initiator.
	 */
	*flags &= ~CAM_DIR_MASK;
	if ((io->io_hdr.flags & CTL_FLAG_DATA_MASK) == CTL_FLAG_DATA_IN)
		*flags |= CAM_DIR_IN;
	else
		*flags |= CAM_DIR_OUT;

	*flags &= ~CAM_DATA_MASK;
	idx = cmd_info->cur_transfer_index;
	off = cmd_info->cur_transfer_off;
	cmd_info->flags &= ~CTLFE_CMD_PIECEWISE;
	if (io->scsiio.kern_sg_entries == 0) {	/* No S/G list. */

		/* One time shift for SRR offset. */
		off += io->scsiio.ext_data_filled;
		io->scsiio.ext_data_filled = 0;

		*data_ptr = io->scsiio.kern_data_ptr + off;
		if (io->scsiio.kern_data_len - off <= bus_softc->maxio) {
			*dxfer_len = io->scsiio.kern_data_len - off;
		} else {
			*dxfer_len = bus_softc->maxio;
			cmd_info->cur_transfer_off += bus_softc->maxio;
			cmd_info->flags |= CTLFE_CMD_PIECEWISE;
		}
		*sglist_cnt = 0;

		if (io->io_hdr.flags & CTL_FLAG_BUS_ADDR)
			*flags |= CAM_DATA_PADDR;
		else
			*flags |= CAM_DATA_VADDR;
	} else {	/* S/G list with physical or virtual pointers. */
		ctl_sglist = (struct ctl_sg_entry *)io->scsiio.kern_data_ptr;

		/* One time shift for SRR offset. */
		while (io->scsiio.ext_data_filled >= ctl_sglist[idx].len - off) {
			io->scsiio.ext_data_filled -= ctl_sglist[idx].len - off;
			idx++;
			off = 0;
		}
		off += io->scsiio.ext_data_filled;
		io->scsiio.ext_data_filled = 0;

		cam_sglist = cmd_info->cam_sglist;
		*dxfer_len = 0;
		for (i = 0; i < io->scsiio.kern_sg_entries - idx; i++) {
			cam_sglist[i].ds_addr = (bus_addr_t)(uintptr_t)ctl_sglist[i + idx].addr + off;
			if (ctl_sglist[i + idx].len - off <= bus_softc->maxio - *dxfer_len) {
				cam_sglist[i].ds_len = ctl_sglist[idx + i].len - off;
				*dxfer_len += cam_sglist[i].ds_len;
			} else {
				cam_sglist[i].ds_len = bus_softc->maxio - *dxfer_len;
				cmd_info->cur_transfer_index = idx + i;
				cmd_info->cur_transfer_off = cam_sglist[i].ds_len + off;
				cmd_info->flags |= CTLFE_CMD_PIECEWISE;
				*dxfer_len += cam_sglist[i].ds_len;
				if (ctl_sglist[i].len != 0)
					i++;
				break;
			}
			if (i == (CTLFE_MAX_SEGS - 1) &&
			    idx + i < (io->scsiio.kern_sg_entries - 1)) {
				cmd_info->cur_transfer_index = idx + i + 1;
				cmd_info->cur_transfer_off = 0;
				cmd_info->flags |= CTLFE_CMD_PIECEWISE;
				i++;
				break;
			}
			off = 0;
		}
		*sglist_cnt = i;
		if (io->io_hdr.flags & CTL_FLAG_BUS_ADDR)
			*flags |= CAM_DATA_SG_PADDR;
		else
			*flags |= CAM_DATA_SG;
		*data_ptr = (uint8_t *)cam_sglist;
	}
}