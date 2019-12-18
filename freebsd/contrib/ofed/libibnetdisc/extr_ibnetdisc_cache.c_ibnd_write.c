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
 int /*<<< orphan*/  IBND_DEBUG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static ssize_t ibnd_write(int fd, const void *buf, size_t count)
{
	size_t count_done = 0;
	ssize_t ret;

	while ((count - count_done) > 0) {
		ret = write(fd, ((char *) buf) + count_done, count - count_done);
		if (ret < 0) {
			if (errno == EINTR)
				continue;
			else {
				IBND_DEBUG("write: %s\n", strerror(errno));
				return -1;
			}
		}
		count_done += ret;
	}
	return count_done;
}