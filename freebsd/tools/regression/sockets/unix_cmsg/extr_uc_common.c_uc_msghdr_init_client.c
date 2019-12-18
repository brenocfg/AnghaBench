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
struct msghdr {size_t msg_controllen; } ;
struct iovec {int dummy; } ;
struct cmsghdr {int cmsg_type; int /*<<< orphan*/  cmsg_len; int /*<<< orphan*/  cmsg_level; } ;
struct TYPE_2__ {scalar_t__ send_array_flag; } ;

/* Variables and functions */
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (size_t) ; 
 size_t CMSG_SPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 TYPE_1__ uc_cfg ; 
 int /*<<< orphan*/  uc_dbgmsg (char*) ; 
 int /*<<< orphan*/  uc_msghdr_init_generic (struct msghdr*,struct iovec*,void*) ; 

void
uc_msghdr_init_client(struct msghdr *msghdr, struct iovec *iov,
    void *cmsg_data, size_t cmsg_size, int type, size_t arr_size)
{
	struct cmsghdr *cmsghdr;

	uc_msghdr_init_generic(msghdr, iov, cmsg_data);
	if (cmsg_data != NULL) {
		if (uc_cfg.send_array_flag)
			uc_dbgmsg("sending an array");
		else
			uc_dbgmsg("sending a scalar");
		msghdr->msg_controllen = uc_cfg.send_array_flag ?
		    cmsg_size : CMSG_SPACE(0);
		cmsghdr = CMSG_FIRSTHDR(msghdr);
		cmsghdr->cmsg_level = SOL_SOCKET;
		cmsghdr->cmsg_type = type;
		cmsghdr->cmsg_len = CMSG_LEN(uc_cfg.send_array_flag ? arr_size : 0);
	} else
		msghdr->msg_controllen = 0;
}