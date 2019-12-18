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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {size_t data_len; scalar_t__ cmd_status; scalar_t__ flags; scalar_t__ timeout; int /*<<< orphan*/  cmd; } ;
struct mfi_dcmd_frame {TYPE_1__ header; int /*<<< orphan*/  opcode; int /*<<< orphan*/  mbox; } ;
struct mfi_ioc_passthru {size_t buf_size; void* buf; struct mfi_dcmd_frame ioc_frame; } ;
typedef  int /*<<< orphan*/  ioc ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  MFIIO_PASSTHRU ; 
 int /*<<< orphan*/  MFI_CMD_DCMD ; 
 size_t MFI_MBOX_SIZE ; 
 scalar_t__ MFI_STAT_OK ; 
 int /*<<< orphan*/  bcopy (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bzero (struct mfi_ioc_passthru*,int) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mfi_ioc_passthru*) ; 
 int /*<<< orphan*/  mfi_status (scalar_t__) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
mfi_dcmd_command(int fd, uint32_t opcode, void *buf, size_t bufsize,
    uint8_t *mbox, size_t mboxlen, uint8_t *statusp)
{
	struct mfi_ioc_passthru ioc;
	struct mfi_dcmd_frame *dcmd;
	int r;

	if ((mbox != NULL && (mboxlen == 0 || mboxlen > MFI_MBOX_SIZE)) ||
	    (mbox == NULL && mboxlen != 0)) {
		errno = EINVAL;
		return (-1);
	}

	bzero(&ioc, sizeof(ioc));
	dcmd = &ioc.ioc_frame;
	if (mbox)
		bcopy(mbox, dcmd->mbox, mboxlen);
	dcmd->header.cmd = MFI_CMD_DCMD;
	dcmd->header.timeout = 0;
	dcmd->header.flags = 0;
	dcmd->header.data_len = bufsize;
	dcmd->opcode = opcode;

	ioc.buf = buf;
	ioc.buf_size = bufsize;
	r = ioctl(fd, MFIIO_PASSTHRU, &ioc);
	if (r < 0)
		return (r);

	if (statusp != NULL)
		*statusp = dcmd->header.cmd_status;
	else if (dcmd->header.cmd_status != MFI_STAT_OK) {
		warnx("Command failed: %s",
		    mfi_status(dcmd->header.cmd_status));
		errno = EIO;
		return (-1);
	}
	return (0);
}