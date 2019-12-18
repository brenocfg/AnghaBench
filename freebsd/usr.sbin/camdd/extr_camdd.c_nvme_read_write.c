#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct nvme_command {int nsid; int cdw10; int cdw11; int cdw12; int /*<<< orphan*/  opc; } ;
struct ccb_nvmeio {struct nvme_command cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  NVME_OPC_READ ; 
 int /*<<< orphan*/  NVME_OPC_WRITE ; 
 int UINT16_MAX ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  cam_fill_nvmeio (struct ccb_nvmeio*,int,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

void
nvme_read_write(struct ccb_nvmeio *nvmeio, uint32_t retries,
		void (*cbfcnp)(struct cam_periph *, union ccb *),
		uint32_t nsid, int readop, uint64_t lba,
		uint32_t block_count, uint8_t *data_ptr, uint32_t dxfer_len,
		uint32_t timeout)
{
	struct nvme_command *nc = &nvmeio->cmd;

	nc->opc = readop ? NVME_OPC_READ : NVME_OPC_WRITE;

	nc->nsid = nsid;

	nc->cdw10 = lba & UINT32_MAX;
	nc->cdw11 = lba >> 32;

	/* NLB (bits 15:0) is a zero based value */
	nc->cdw12 = (block_count - 1) & UINT16_MAX;

	cam_fill_nvmeio(nvmeio,
			retries,
			cbfcnp,
			readop ? CAM_DIR_IN : CAM_DIR_OUT,
			data_ptr,
			dxfer_len,
			timeout);
}