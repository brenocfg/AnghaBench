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
typedef  void* uint32_t ;
struct mps_usr_command {int len; void* flags; void* buf; void* rpl_len; void* rpl; void* req_len; void* req; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPRIO_MPR_COMMAND ; 
 int /*<<< orphan*/  MPSIO_MPS_COMMAND ; 
 int /*<<< orphan*/  bzero (struct mps_usr_command*,int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mps_usr_command*) ; 
 scalar_t__ is_mps ; 

int
mps_user_command(int fd, void *req, uint32_t req_len, void *reply,
        uint32_t reply_len, void *buffer, int len, uint32_t flags)
{
	struct mps_usr_command cmd;

	bzero(&cmd, sizeof(struct mps_usr_command));
	cmd.req = req;
	cmd.req_len = req_len;
	cmd.rpl = reply;
	cmd.rpl_len = reply_len;
	cmd.buf = buffer;
	cmd.len = len;
	cmd.flags = flags;

	if (ioctl(fd, is_mps ? MPSIO_MPS_COMMAND : MPRIO_MPR_COMMAND, &cmd) < 0)
		return (errno);
	return (0);
}