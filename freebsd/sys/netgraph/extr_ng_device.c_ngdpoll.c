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
struct cdev {int /*<<< orphan*/  si_drv1; } ;
typedef  TYPE_1__* priv_p ;
struct TYPE_2__ {int /*<<< orphan*/  readq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int POLLIN ; 
 int POLLRDNORM ; 

__attribute__((used)) static int
ngdpoll(struct cdev *dev, int events, struct thread *td)
{
	priv_p	priv = (priv_p )dev->si_drv1;
	int revents = 0;

	if (events & (POLLIN | POLLRDNORM) &&
	    !IFQ_IS_EMPTY(&priv->readq))
		revents |= events & (POLLIN | POLLRDNORM);

	return (revents);
}