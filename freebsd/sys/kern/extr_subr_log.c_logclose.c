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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {scalar_t__ sc_state; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_sigio; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ *) ; 
 scalar_t__ log_open ; 
 TYPE_1__ logsoftc ; 
 int /*<<< orphan*/  msgbuf_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
logclose(struct cdev *dev, int flag, int mode, struct thread *td)
{

	funsetown(&logsoftc.sc_sigio);

	mtx_lock(&msgbuf_lock);
	callout_stop(&logsoftc.sc_callout);
	logsoftc.sc_state = 0;
	log_open = 0;
	mtx_unlock(&msgbuf_lock);

	return (0);
}