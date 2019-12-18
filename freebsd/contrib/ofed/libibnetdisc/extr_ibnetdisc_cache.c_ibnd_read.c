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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  IBND_DEBUG (char*,...) ; 
 scalar_t__ errno ; 
 scalar_t__ read (int,char*,size_t) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static ssize_t ibnd_read(int fd, void *buf, size_t count)
{
	size_t count_done = 0;
	ssize_t ret;

	while ((count - count_done) > 0) {
		ret = read(fd, ((char *) buf) + count_done, count - count_done);
		if (ret < 0) {
			if (errno == EINTR)
				continue;
			else {
				IBND_DEBUG("read: %s\n", strerror(errno));
				return -1;
			}
		}
		if (!ret)
			break;
		count_done += ret;
	}

	if (count_done != count) {
		IBND_DEBUG("read: read short\n");
		return -1;
	}

	return count_done;
}