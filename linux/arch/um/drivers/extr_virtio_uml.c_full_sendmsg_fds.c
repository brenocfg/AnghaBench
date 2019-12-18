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

/* Variables and functions */
 int EINTR ; 
 int os_sendmsg_fds (int,void const*,unsigned int,int const*,unsigned int) ; 

__attribute__((used)) static int full_sendmsg_fds(int fd, const void *buf, unsigned int len,
			    const int *fds, unsigned int fds_num)
{
	int rc;

	do {
		rc = os_sendmsg_fds(fd, buf, len, fds, fds_num);
		if (rc > 0) {
			buf += rc;
			len -= rc;
			fds = NULL;
			fds_num = 0;
		}
	} while (len && (rc >= 0 || rc == -EINTR));

	if (rc < 0)
		return rc;
	return 0;
}