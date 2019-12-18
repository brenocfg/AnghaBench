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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct tuntap_softc {TYPE_1__ tun_rsel; } ;
struct knote {int kn_filter; struct tuntap_softc* kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct ifnet {int /*<<< orphan*/  if_xname; } ;
struct cdev {struct tuntap_softc* si_drv1; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 struct ifnet* TUN2IFP (struct tuntap_softc*) ; 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_read_filterops ; 
 int /*<<< orphan*/  tun_write_filterops ; 

__attribute__((used)) static int
tunkqfilter(struct cdev *dev, struct knote *kn)
{
	struct tuntap_softc	*tp = dev->si_drv1;
	struct ifnet	*ifp = TUN2IFP(tp);

	switch(kn->kn_filter) {
	case EVFILT_READ:
		TUNDEBUG(ifp, "%s kqfilter: EVFILT_READ, minor = %#x\n",
		    ifp->if_xname, dev2unit(dev));
		kn->kn_fop = &tun_read_filterops;
		break;

	case EVFILT_WRITE:
		TUNDEBUG(ifp, "%s kqfilter: EVFILT_WRITE, minor = %#x\n",
		    ifp->if_xname, dev2unit(dev));
		kn->kn_fop = &tun_write_filterops;
		break;

	default:
		TUNDEBUG(ifp, "%s kqfilter: invalid filter, minor = %#x\n",
		    ifp->if_xname, dev2unit(dev));
		return(EINVAL);
	}

	kn->kn_hook = tp;
	knlist_add(&tp->tun_rsel.si_note, kn, 0);

	return (0);
}