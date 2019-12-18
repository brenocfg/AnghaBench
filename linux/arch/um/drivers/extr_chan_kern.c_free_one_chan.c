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
struct chan {int /*<<< orphan*/  fd; scalar_t__ output; scalar_t__ primary; int /*<<< orphan*/  data; TYPE_1__* ops; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  close_one_chan (struct chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_sigio_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_one_chan(struct chan *chan)
{
	list_del(&chan->list);

	close_one_chan(chan, 0);

	if (chan->ops->free != NULL)
		(*chan->ops->free)(chan->data);

	if (chan->primary && chan->output)
		ignore_sigio_fd(chan->fd);
	kfree(chan);
}