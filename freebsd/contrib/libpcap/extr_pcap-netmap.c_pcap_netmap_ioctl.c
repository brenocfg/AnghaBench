#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
struct pcap_netmap {struct nm_desc* d; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_name; } ;
struct nm_desc {int fd; TYPE_1__ req; } ;
struct ifreq {int ifr_flags; int ifr_flagshigh; int /*<<< orphan*/  ifr_name; } ;
struct TYPE_5__ {struct pcap_netmap* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
#define  SIOCGIFFLAGS 129 
#define  SIOCSIFFLAGS 128 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pcap_netmap_ioctl(pcap_t *p, u_long what, uint32_t *if_flags)
{
	struct pcap_netmap *pn = p->priv;
	struct nm_desc *d = pn->d;
	struct ifreq ifr;
	int error, fd = d->fd;

#ifdef linux
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		fprintf(stderr, "Error: cannot get device control socket.\n");
		return -1;
	}
#endif /* linux */
	bzero(&ifr, sizeof(ifr));
	strncpy(ifr.ifr_name, d->req.nr_name, sizeof(ifr.ifr_name));
	switch (what) {
	case SIOCSIFFLAGS:
		/*
		 * The flags we pass in are 32-bit and unsigned.
		 *
		 * On most if not all UN*Xes, ifr_flags is 16-bit and
		 * signed, and the result of assigning a longer
		 * unsigned value to a shorter signed value is
		 * implementation-defined (even if, in practice, it'll
		 * do what's intended on all platforms we support
		 * result of assigning a 32-bit unsigned value).
		 * So we mask out the upper 16 bits.
		 */
		ifr.ifr_flags = *if_flags & 0xffff;
#ifdef __FreeBSD__
		/*
		 * In FreeBSD, we need to set the high-order flags,
		 * as we're using IFF_PPROMISC, which is in those bits.
		 *
		 * XXX - DragonFly BSD?
		 */
		ifr.ifr_flagshigh = *if_flags >> 16;
#endif /* __FreeBSD__ */
		break;
	}
	error = ioctl(fd, what, &ifr);
	if (!error) {
		switch (what) {
		case SIOCGIFFLAGS:
			/*
			 * The flags we return are 32-bit.
			 *
			 * On most if not all UN*Xes, ifr_flags is
			 * 16-bit and signed, and will get sign-
			 * extended, so that the upper 16 bits of
			 * those flags will be forced on.  So we
			 * mask out the upper 16 bits of the
			 * sign-extended value.
			 */
			*if_flags = ifr.ifr_flags & 0xffff;
#ifdef __FreeBSD__
			/*
			 * In FreeBSD, we need to return the
			 * high-order flags, as we're using
			 * IFF_PPROMISC, which is in those bits.
			 *
			 * XXX - DragonFly BSD?
			 */
			*if_flags |= (ifr.ifr_flagshigh << 16);
#endif /* __FreeBSD__ */
		}
	}
#ifdef linux
	close(fd);
#endif /* linux */
	return error ? -1 : 0;
}