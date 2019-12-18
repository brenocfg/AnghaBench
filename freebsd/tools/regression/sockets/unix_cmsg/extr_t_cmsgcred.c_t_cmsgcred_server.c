#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct msghdr {int dummy; } ;
struct iovec {int dummy; } ;
struct cmsghdr {int dummy; } ;
struct cmsgcred {int dummy; } ;
struct TYPE_3__ {int msg_num; } ;
struct TYPE_4__ {scalar_t__ sock_type; TYPE_1__ ipc_msg; } ;

/* Variables and functions */
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 size_t CMSG_SPACE (int) ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t) ; 
 TYPE_2__ uc_cfg ; 
 scalar_t__ uc_check_msghdr (struct msghdr*,int) ; 
 scalar_t__ uc_check_scm_creds_cmsgcred (struct cmsghdr*) ; 
 int /*<<< orphan*/  uc_dbgmsg (char*,int) ; 
 int /*<<< orphan*/  uc_logmsg (char*) ; 
 scalar_t__ uc_message_recv (int,struct msghdr*) ; 
 int /*<<< orphan*/  uc_msghdr_init_server (struct msghdr*,struct iovec*,void*,size_t) ; 
 int uc_socket_accept (int) ; 
 scalar_t__ uc_socket_close (int) ; 
 scalar_t__ uc_sync_send () ; 

__attribute__((used)) static int
t_cmsgcred_server(int fd1)
{
	struct msghdr msghdr;
	struct iovec iov[1];
	struct cmsghdr *cmsghdr;
	void *cmsg_data;
	size_t cmsg_size;
	u_int i;
	int fd2, rv;

	if (uc_sync_send() < 0)
		return (-2);

	fd2 = -1;
	rv = -2;

	cmsg_size = CMSG_SPACE(sizeof(struct cmsgcred));
	cmsg_data = malloc(cmsg_size);
	if (cmsg_data == NULL) {
		uc_logmsg("malloc");
		goto done;
	}

	if (uc_cfg.sock_type == SOCK_STREAM) {
		fd2 = uc_socket_accept(fd1);
		if (fd2 < 0)
			goto done;
	} else
		fd2 = fd1;

	rv = -1;
	for (i = 1; i <= uc_cfg.ipc_msg.msg_num; ++i) {
		uc_dbgmsg("message #%u", i);

		uc_msghdr_init_server(&msghdr, iov, cmsg_data, cmsg_size);
		if (uc_message_recv(fd2, &msghdr) < 0) {
			rv = -2;
			break;
		}

		if (uc_check_msghdr(&msghdr, sizeof(*cmsghdr)) < 0)
			break;

		cmsghdr = CMSG_FIRSTHDR(&msghdr);
		if (uc_check_scm_creds_cmsgcred(cmsghdr) < 0)
			break;
	}
	if (i > uc_cfg.ipc_msg.msg_num)
		rv = 0;
done:
	free(cmsg_data);
	if (uc_cfg.sock_type == SOCK_STREAM && fd2 >= 0)
		if (uc_socket_close(fd2) < 0)
			rv = -2;
	return (rv);
}