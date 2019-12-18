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
struct port_chan {char* dev; int /*<<< orphan*/  tt; scalar_t__ raw; int /*<<< orphan*/  kernel_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int port_wait (int /*<<< orphan*/ ) ; 
 int raw (int) ; 
 int tcgetattr (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int port_open(int input, int output, int primary, void *d,
		     char **dev_out)
{
	struct port_chan *data = d;
	int fd, err;

	fd = port_wait(data->kernel_data);
	if ((fd >= 0) && data->raw) {
		CATCH_EINTR(err = tcgetattr(fd, &data->tt));
		if (err)
			return err;

		err = raw(fd);
		if (err)
			return err;
	}
	*dev_out = data->dev;
	return fd;
}