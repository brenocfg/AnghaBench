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
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 
 scalar_t__ read (int,char*,size_t) ; 
 scalar_t__ timed_out () ; 

__attribute__((used)) static void
pdu_read(int fd, char *data, size_t len)
{
	ssize_t ret;

	while (len > 0) {
		ret = read(fd, data, len);
		if (ret < 0) {
			if (timed_out())
				log_errx(1, "exiting due to timeout");
			log_err(1, "read");
		} else if (ret == 0)
			log_errx(1, "read: connection lost");
		len -= ret;
		data += ret;
	}
}