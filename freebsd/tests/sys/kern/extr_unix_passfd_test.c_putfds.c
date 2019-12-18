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
struct cmsghdr {int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; int /*<<< orphan*/  cmsg_len; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 int /*<<< orphan*/  SCM_RIGHTS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 

__attribute__((used)) static void
putfds(char *buf, int fd, int nfds)
{
	struct cmsghdr *cm;
	int *fdp, i;

	cm = (struct cmsghdr *)buf;
	cm->cmsg_len = CMSG_LEN(nfds * sizeof(int));
	cm->cmsg_level = SOL_SOCKET;
	cm->cmsg_type = SCM_RIGHTS;
	for (fdp = (int *)CMSG_DATA(cm), i = 0; i < nfds; i++)
		*fdp++ = fd;
}