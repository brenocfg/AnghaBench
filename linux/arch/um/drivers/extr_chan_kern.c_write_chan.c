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
struct chan {scalar_t__ primary; int /*<<< orphan*/  data; int /*<<< orphan*/  fd; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

int write_chan(struct chan *chan, const char *buf, int len,
	       int write_irq)
{
	int n, ret = 0;

	if (len == 0 || !chan || !chan->ops->write)
		return 0;

	n = chan->ops->write(chan->fd, buf, len, chan->data);
	if (chan->primary) {
		ret = n;
	}
	return ret;
}