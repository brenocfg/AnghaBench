#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tuntap_softc {int /*<<< orphan*/  tun_rsel; } ;
struct thread {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifq_len; } ;
struct ifnet {TYPE_1__ if_snd; } ;
struct cdev {struct tuntap_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_IS_EMPTY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFQ_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  IFQ_UNLOCK (TYPE_1__*) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 struct ifnet* TUN2IFP (struct tuntap_softc*) ; 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*,...) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
tunpoll(struct cdev *dev, int events, struct thread *td)
{
	struct tuntap_softc *tp = dev->si_drv1;
	struct ifnet	*ifp = TUN2IFP(tp);
	int		revents = 0;

	TUNDEBUG(ifp, "tunpoll\n");

	if (events & (POLLIN | POLLRDNORM)) {
		IFQ_LOCK(&ifp->if_snd);
		if (!IFQ_IS_EMPTY(&ifp->if_snd)) {
			TUNDEBUG(ifp, "tunpoll q=%d\n", ifp->if_snd.ifq_len);
			revents |= events & (POLLIN | POLLRDNORM);
		} else {
			TUNDEBUG(ifp, "tunpoll waiting\n");
			selrecord(td, &tp->tun_rsel);
		}
		IFQ_UNLOCK(&ifp->if_snd);
	}
	revents |= events & (POLLOUT | POLLWRNORM);

	return (revents);
}