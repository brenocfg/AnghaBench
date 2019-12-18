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
typedef  int uint32_t ;
struct TYPE_2__ {int opc; void* cdw12; void* cdw11; void* cdw10; } ;
struct nvme_pt_command {size_t len; int is_read; int /*<<< orphan*/  cpl; int /*<<< orphan*/ * buf; TYPE_1__ cmd; } ;
typedef  int /*<<< orphan*/  pt ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_PASSTHROUGH_CMD ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 void* htole32 (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  memset (struct nvme_pt_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
wdc_get_data(int fd, uint32_t opcode, uint32_t len, uint32_t off, uint32_t cmd,
    uint8_t *buffer, size_t buflen)
{
	struct nvme_pt_command	pt;

	memset(&pt, 0, sizeof(pt));
	pt.cmd.opc = opcode;
	pt.cmd.cdw10 = htole32(len / sizeof(uint32_t));	/* - 1 like all the others ??? */
	pt.cmd.cdw11 = htole32(off / sizeof(uint32_t));
	pt.cmd.cdw12 = htole32(cmd);
	pt.buf = buffer;
	pt.len = buflen;
	pt.is_read = 1;
//	printf("opcode %#x cdw10(len) %#x cdw11(offset?) %#x cdw12(cmd/sub) %#x buflen %zd\n",
//	    (int)opcode, (int)cdw10, (int)cdw11, (int)cdw12, buflen);

	if (ioctl(fd, NVME_PASSTHROUGH_CMD, &pt) < 0)
		err(1, "wdc_get_data request failed");
	if (nvme_completion_is_error(&pt.cpl))
		errx(1, "wdc_get_data request returned error");
}