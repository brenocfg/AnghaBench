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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {void* cdw11; void* cdw10; int /*<<< orphan*/  opc; } ;
struct nvme_pt_command {int /*<<< orphan*/  cpl; scalar_t__ is_read; scalar_t__ len; void* buf; TYPE_1__ cmd; } ;
typedef  int /*<<< orphan*/  pt ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ NVME_MAX_XFER_SIZE ; 
 int /*<<< orphan*/  NVME_OPC_FIRMWARE_IMAGE_DOWNLOAD ; 
 int /*<<< orphan*/  NVME_PASSTHROUGH_CMD ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* aligned_alloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 void* htole32 (scalar_t__) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct nvme_pt_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
update_firmware(int fd, uint8_t *payload, int32_t payload_size)
{
	struct nvme_pt_command	pt;
	int32_t			off, resid, size;
	void			*chunk;

	off = 0;
	resid = payload_size;

	if ((chunk = aligned_alloc(PAGE_SIZE, NVME_MAX_XFER_SIZE)) == NULL)
		errx(1, "unable to malloc %d bytes", NVME_MAX_XFER_SIZE);

	while (resid > 0) {
		size = (resid >= NVME_MAX_XFER_SIZE) ?
		    NVME_MAX_XFER_SIZE : resid;
		memcpy(chunk, payload + off, size);

		memset(&pt, 0, sizeof(pt));
		pt.cmd.opc = NVME_OPC_FIRMWARE_IMAGE_DOWNLOAD;
		pt.cmd.cdw10 = htole32((size / sizeof(uint32_t)) - 1);
		pt.cmd.cdw11 = htole32(off / sizeof(uint32_t));
		pt.buf = chunk;
		pt.len = size;
		pt.is_read = 0;

		if (ioctl(fd, NVME_PASSTHROUGH_CMD, &pt) < 0)
			err(1, "firmware download request failed");

		if (nvme_completion_is_error(&pt.cpl))
			errx(1, "firmware download request returned error");

		resid -= size;
		off += size;
	}
}