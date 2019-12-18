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
struct chan {int opened; int fd; int /*<<< orphan*/  data; TYPE_1__* ops; int /*<<< orphan*/  dev; int /*<<< orphan*/  primary; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int (* open ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int os_set_fd_block (int,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_one_chan(struct chan *chan)
{
	int fd, err;

	if (chan->opened)
		return 0;

	if (chan->ops->open == NULL)
		fd = 0;
	else fd = (*chan->ops->open)(chan->input, chan->output, chan->primary,
				     chan->data, &chan->dev);
	if (fd < 0)
		return fd;

	err = os_set_fd_block(fd, 0);
	if (err) {
		(*chan->ops->close)(fd, chan->data);
		return err;
	}

	chan->fd = fd;

	chan->opened = 1;
	return 0;
}