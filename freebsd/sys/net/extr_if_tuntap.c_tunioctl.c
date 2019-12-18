#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct virtio_net_hdr_mrg_rxbuf {int dummy; } ;
struct virtio_net_hdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  octet; } ;
struct tuntap_softc {int tun_flags; int tun_vhdrlen; int /*<<< orphan*/  tun_sigio; int /*<<< orphan*/  tun_pid; TYPE_1__ tun_ether; } ;
struct tuninfo {int /*<<< orphan*/  baudrate; int /*<<< orphan*/  type; int /*<<< orphan*/  mtu; } ;
struct thread {int dummy; } ;
struct mbuf {int m_len; struct mbuf* m_next; } ;
struct ifreq {int /*<<< orphan*/  ifr_mtu; int /*<<< orphan*/  ifr_name; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_baudrate; int /*<<< orphan*/  if_type; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_vnet; int /*<<< orphan*/  if_xname; } ;
struct cdev {struct tuntap_softc* si_drv1; } ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_6__ {TYPE_2__* td_proc; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOTTY ; 
 int EPROTOTYPE ; 
#define  FIOASYNC 151 
#define  FIOGETOWN 150 
#define  FIONBIO 149 
#define  FIONREAD 148 
#define  FIOSETOWN 147 
#define  IFF_BROADCAST 146 
 int IFF_CANTCHANGE ; 
 int IFF_MULTICAST ; 
#define  IFF_POINTOPOINT 145 
 int IFF_UP ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  IFQ_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_POLL_NOLOCK (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_UNLOCK (int /*<<< orphan*/ *) ; 
 int IOCPARM_IVAL (int /*<<< orphan*/ *) ; 
#define  SIOCGIFADDR 144 
#define  SIOCSIFADDR 143 
 int /*<<< orphan*/  SIOCSIFMTU ; 
#define  TAPGVNETHDR 142 
#define  TAPSVNETHDR 141 
#define  TIOCGPGRP 140 
#define  TIOCSPGRP 139 
 struct ifnet* TUN2IFP (struct tuntap_softc*) ; 
#define  TUNGDEBUG 138 
#define  TUNGIFHEAD 137 
#define  TUNGIFINFO 136 
#define  TUNGIFNAME 135 
#define  TUNSDEBUG 134 
#define  TUNSIFHEAD 133 
#define  TUNSIFINFO 132 
#define  TUNSIFMODE 131 
#define  TUNSIFPID 130 
#define  TUNSLMODE 129 
 int TUN_ASYNC ; 
 int TUN_IFHEAD ; 
 int TUN_L2 ; 
 int TUN_LMODE ; 
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int TUN_VMIO_FLAG_MASK ; 
#define  VMIO_SIOCSIFFLAGS 128 
 int _IO (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* curthread ; 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int ifhwioctl (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_vnethdr_set (struct ifnet*,int) ; 
 int tundebug ; 

__attribute__((used)) static	int
tunioctl(struct cdev *dev, u_long cmd, caddr_t data, int flag,
    struct thread *td)
{
	struct ifreq ifr, *ifrp;
	struct tuntap_softc *tp = dev->si_drv1;
	struct ifnet *ifp = TUN2IFP(tp);
	struct tuninfo *tunp;
	int error, iflags, ival;
	bool	l2tun;

	l2tun = (tp->tun_flags & TUN_L2) != 0;
	if (l2tun) {
		/* tap specific ioctls */
		switch(cmd) {
		/* VMware/VMnet port ioctl's */
#if defined(COMPAT_FREEBSD6) || defined(COMPAT_FREEBSD5) || \
    defined(COMPAT_FREEBSD4)
		case _IO('V', 0):
			ival = IOCPARM_IVAL(data);
			data = (caddr_t)&ival;
			/* FALLTHROUGH */
#endif
		case VMIO_SIOCSIFFLAGS: /* VMware/VMnet SIOCSIFFLAGS */
			iflags = *(int *)data;
			iflags &= TUN_VMIO_FLAG_MASK;
			iflags &= ~IFF_CANTCHANGE;
			iflags |= IFF_UP;

			TUN_LOCK(tp);
			ifp->if_flags = iflags |
			    (ifp->if_flags & IFF_CANTCHANGE);
			TUN_UNLOCK(tp);

			return (0);
		case SIOCGIFADDR:	/* get MAC address of the remote side */
			TUN_LOCK(tp);
			bcopy(&tp->tun_ether.octet, data,
			    sizeof(tp->tun_ether.octet));
			TUN_UNLOCK(tp);

			return (0);
		case SIOCSIFADDR:	/* set MAC address of the remote side */
			TUN_LOCK(tp);
			bcopy(data, &tp->tun_ether.octet,
			    sizeof(tp->tun_ether.octet));
			TUN_UNLOCK(tp);

			return (0);
		case TAPSVNETHDR:
			ival = *(int *)data;
			if (ival != 0 &&
			    ival != sizeof(struct virtio_net_hdr) &&
			    ival != sizeof(struct virtio_net_hdr_mrg_rxbuf)) {
				return (EINVAL);
			}
			TUN_LOCK(tp);
			tun_vnethdr_set(ifp, ival);
			TUN_UNLOCK(tp);

			return (0);
		case TAPGVNETHDR:
			TUN_LOCK(tp);
			*(int *)data = tp->tun_vhdrlen;
			TUN_UNLOCK(tp);

			return (0);
		}

		/* Fall through to the common ioctls if unhandled */
	} else {
		switch (cmd) {
		case TUNSLMODE:
			TUN_LOCK(tp);
			if (*(int *)data) {
				tp->tun_flags |= TUN_LMODE;
				tp->tun_flags &= ~TUN_IFHEAD;
			} else
				tp->tun_flags &= ~TUN_LMODE;
			TUN_UNLOCK(tp);

			return (0);
		case TUNSIFHEAD:
			TUN_LOCK(tp);
			if (*(int *)data) {
				tp->tun_flags |= TUN_IFHEAD;
				tp->tun_flags &= ~TUN_LMODE;
			} else
				tp->tun_flags &= ~TUN_IFHEAD;
			TUN_UNLOCK(tp);

			return (0);
		case TUNGIFHEAD:
			TUN_LOCK(tp);
			*(int *)data = (tp->tun_flags & TUN_IFHEAD) ? 1 : 0;
			TUN_UNLOCK(tp);

			return (0);
		case TUNSIFMODE:
			/* deny this if UP */
			if (TUN2IFP(tp)->if_flags & IFF_UP)
				return (EBUSY);

			switch (*(int *)data & ~IFF_MULTICAST) {
			case IFF_POINTOPOINT:
			case IFF_BROADCAST:
				TUN_LOCK(tp);
				TUN2IFP(tp)->if_flags &=
				    ~(IFF_BROADCAST|IFF_POINTOPOINT|IFF_MULTICAST);
				TUN2IFP(tp)->if_flags |= *(int *)data;
				TUN_UNLOCK(tp);

				break;
			default:
				return (EINVAL);
			}

			return (0);
		case TUNSIFPID:
			TUN_LOCK(tp);
			tp->tun_pid = curthread->td_proc->p_pid;
			TUN_UNLOCK(tp);

			return (0);
		}
		/* Fall through to the common ioctls if unhandled */
	}

	switch (cmd) {
	case TUNGIFNAME:
		ifrp = (struct ifreq *)data;
		strlcpy(ifrp->ifr_name, TUN2IFP(tp)->if_xname, IFNAMSIZ);

		return (0);
	case TUNSIFINFO:
		tunp = (struct tuninfo *)data;
		if (TUN2IFP(tp)->if_type != tunp->type)
			return (EPROTOTYPE);
		TUN_LOCK(tp);
		if (TUN2IFP(tp)->if_mtu != tunp->mtu) {
			strlcpy(ifr.ifr_name, if_name(TUN2IFP(tp)), IFNAMSIZ);
			ifr.ifr_mtu = tunp->mtu;
			CURVNET_SET(TUN2IFP(tp)->if_vnet);
			error = ifhwioctl(SIOCSIFMTU, TUN2IFP(tp),
			    (caddr_t)&ifr, td);
			CURVNET_RESTORE();
			if (error) {
				TUN_UNLOCK(tp);
				return (error);
			}
		}
		TUN2IFP(tp)->if_baudrate = tunp->baudrate;
		TUN_UNLOCK(tp);
		break;
	case TUNGIFINFO:
		tunp = (struct tuninfo *)data;
		TUN_LOCK(tp);
		tunp->mtu = TUN2IFP(tp)->if_mtu;
		tunp->type = TUN2IFP(tp)->if_type;
		tunp->baudrate = TUN2IFP(tp)->if_baudrate;
		TUN_UNLOCK(tp);
		break;
	case TUNSDEBUG:
		tundebug = *(int *)data;
		break;
	case TUNGDEBUG:
		*(int *)data = tundebug;
		break;
	case FIONBIO:
		break;
	case FIOASYNC:
		TUN_LOCK(tp);
		if (*(int *)data)
			tp->tun_flags |= TUN_ASYNC;
		else
			tp->tun_flags &= ~TUN_ASYNC;
		TUN_UNLOCK(tp);
		break;
	case FIONREAD:
		if (!IFQ_IS_EMPTY(&TUN2IFP(tp)->if_snd)) {
			struct mbuf *mb;
			IFQ_LOCK(&TUN2IFP(tp)->if_snd);
			IFQ_POLL_NOLOCK(&TUN2IFP(tp)->if_snd, mb);
			for (*(int *)data = 0; mb != NULL; mb = mb->m_next)
				*(int *)data += mb->m_len;
			IFQ_UNLOCK(&TUN2IFP(tp)->if_snd);
		} else
			*(int *)data = 0;
		break;
	case FIOSETOWN:
		return (fsetown(*(int *)data, &tp->tun_sigio));

	case FIOGETOWN:
		*(int *)data = fgetown(&tp->tun_sigio);
		return (0);

	/* This is deprecated, FIOSETOWN should be used instead. */
	case TIOCSPGRP:
		return (fsetown(-(*(int *)data), &tp->tun_sigio));

	/* This is deprecated, FIOGETOWN should be used instead. */
	case TIOCGPGRP:
		*(int *)data = -fgetown(&tp->tun_sigio);
		return (0);

	default:
		return (ENOTTY);
	}
	return (0);
}