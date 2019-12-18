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
struct TYPE_2__ {int status; } ;
union ctl_io {TYPE_1__ io_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_IO ; 
 int CTL_STATUS_MASK ; 
 int CTL_SUCCESS ; 
 int ioctl (int,int /*<<< orphan*/ ,union ctl_io*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
cctl_do_io(int fd, int retries, union ctl_io *io, const char *func)
{
	do {
		if (ioctl(fd, CTL_IO, io) == -1) {
			warn("%s: error sending CTL_IO ioctl", func);
			return (-1);
		}
	} while (((io->io_hdr.status & CTL_STATUS_MASK) != CTL_SUCCESS)
	      && (retries-- > 0));

	return (0);
}