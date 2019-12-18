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
struct fd_chan {int fd; char* str; int /*<<< orphan*/  tt; scalar_t__ raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 scalar_t__ isatty (int) ; 
 int raw (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int tcgetattr (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fd_open(int input, int output, int primary, void *d, char **dev_out)
{
	struct fd_chan *data = d;
	int err;

	if (data->raw && isatty(data->fd)) {
		CATCH_EINTR(err = tcgetattr(data->fd, &data->tt));
		if (err)
			return err;

		err = raw(data->fd);
		if (err)
			return err;
	}
	sprintf(data->str, "%d", data->fd);
	*dev_out = data->str;
	return data->fd;
}