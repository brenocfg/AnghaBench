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
struct cmsghdr {int /*<<< orphan*/  cmsg_len; int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; } ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  SCM_RIGHTS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
msghdr_add_fd(struct cmsghdr *cmsg, int fd)
{

	PJDLOG_ASSERT(fd >= 0);

	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(sizeof(fd));
	bcopy(&fd, CMSG_DATA(cmsg), sizeof(fd));

	return (0);
}