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
 int ECONNRESET ; 
 int EINTR ; 
 int os_read_file (int,void*,int) ; 

__attribute__((used)) static int full_read(int fd, void *buf, int len)
{
	int rc;

	do {
		rc = os_read_file(fd, buf, len);
		if (rc > 0) {
			buf += rc;
			len -= rc;
		}
	} while (len && (rc > 0 || rc == -EINTR));

	if (rc < 0)
		return rc;
	if (rc == 0)
		return -ECONNRESET;
	return 0;
}