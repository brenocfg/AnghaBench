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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct lifreq {char const* lifr_name; int lifr_flags; int /*<<< orphan*/  lifr_addr; int /*<<< orphan*/  lifr_dstaddr; int /*<<< orphan*/  lifr_broadaddr; } ;
struct lifnum {int lifn_count; scalar_t__ lifn_flags; void* lifn_family; } ;
struct lifconf {unsigned int lifc_len; char* lifc_buf; scalar_t__ lifc_flags; void* lifc_family; } ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
typedef  int /*<<< orphan*/  get_if_flags_func ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 void* AF_UNSPEC ; 
 scalar_t__ EADDRNOTAVAIL ; 
 scalar_t__ ENXIO ; 
 int IFF_BROADCAST ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  SIOCGLIFBRDADDR ; 
 int /*<<< orphan*/  SIOCGLIFCONF ; 
 int /*<<< orphan*/  SIOCGLIFDSTADDR ; 
 int /*<<< orphan*/  SIOCGLIFFLAGS ; 
 int /*<<< orphan*/  SIOCGLIFNETMASK ; 
 int /*<<< orphan*/  SIOCGLIFNUM ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ add_addr_to_if (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,struct sockaddr*,int,struct sockaddr*,int,struct sockaddr*,int,struct sockaddr*,int,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char const*,char const*,int) ; 
 int stub1 (char const*) ; 

int
pcap_findalldevs_interfaces(pcap_if_list_t *devlistp, char *errbuf,
    int (*check_usable)(const char *), get_if_flags_func get_flags_func)
{
	register int fd4, fd6, fd;
	register struct lifreq *ifrp, *ifend;
	struct lifnum ifn;
	struct lifconf ifc;
	char *buf = NULL;
	unsigned buf_size;
#ifdef HAVE_SOLARIS
	char *p, *q;
#endif
	struct lifreq ifrflags, ifrnetmask, ifrbroadaddr, ifrdstaddr;
	struct sockaddr *netmask, *broadaddr, *dstaddr;
	int ret = 0;

	/*
	 * Create a socket from which to fetch the list of interfaces,
	 * and from which to fetch IPv4 information.
	 */
	fd4 = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd4 < 0) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "socket: AF_INET");
		return (-1);
	}

	/*
	 * Create a socket from which to fetch IPv6 information.
	 */
	fd6 = socket(AF_INET6, SOCK_DGRAM, 0);
	if (fd6 < 0) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "socket: AF_INET6");
		(void)close(fd4);
		return (-1);
	}

	/*
	 * How many entries will SIOCGLIFCONF return?
	 */
	ifn.lifn_family = AF_UNSPEC;
	ifn.lifn_flags = 0;
	ifn.lifn_count = 0;
	if (ioctl(fd4, SIOCGLIFNUM, (char *)&ifn) < 0) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "SIOCGLIFNUM");
		(void)close(fd6);
		(void)close(fd4);
		return (-1);
	}

	/*
	 * Allocate a buffer for those entries.
	 */
	buf_size = ifn.lifn_count * sizeof (struct lifreq);
	buf = malloc(buf_size);
	if (buf == NULL) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		(void)close(fd6);
		(void)close(fd4);
		return (-1);
	}

	/*
	 * Get the entries.
	 */
	ifc.lifc_len = buf_size;
	ifc.lifc_buf = buf;
	ifc.lifc_family = AF_UNSPEC;
	ifc.lifc_flags = 0;
	memset(buf, 0, buf_size);
	if (ioctl(fd4, SIOCGLIFCONF, (char *)&ifc) < 0) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "SIOCGLIFCONF");
		(void)close(fd6);
		(void)close(fd4);
		free(buf);
		return (-1);
	}

	/*
	 * Loop over the entries.
	 */
	ifrp = (struct lifreq *)buf;
	ifend = (struct lifreq *)(buf + ifc.lifc_len);

	for (; ifrp < ifend; ifrp++) {
		/*
		 * Skip entries that begin with "dummy".
		 * XXX - what are these?  Is this Linux-specific?
		 * Are there platforms on which we shouldn't do this?
		 */
		if (strncmp(ifrp->lifr_name, "dummy", 5) == 0)
			continue;

		/*
		 * Can we capture on this device?
		 */
		if (!(*check_usable)(ifrp->lifr_name)) {
			/*
			 * No.
			 */
			continue;
		}

		/*
		 * IPv6 or not?
		 */
		if (((struct sockaddr *)&ifrp->lifr_addr)->sa_family == AF_INET6)
			fd = fd6;
		else
			fd = fd4;

		/*
		 * Get the flags for this interface.
		 */
		strncpy(ifrflags.lifr_name, ifrp->lifr_name,
		    sizeof(ifrflags.lifr_name));
		if (ioctl(fd, SIOCGLIFFLAGS, (char *)&ifrflags) < 0) {
			if (errno == ENXIO)
				continue;
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "SIOCGLIFFLAGS: %.*s",
			    (int)sizeof(ifrflags.lifr_name),
			    ifrflags.lifr_name);
			ret = -1;
			break;
		}

		/*
		 * Get the netmask for this address on this interface.
		 */
		strncpy(ifrnetmask.lifr_name, ifrp->lifr_name,
		    sizeof(ifrnetmask.lifr_name));
		memcpy(&ifrnetmask.lifr_addr, &ifrp->lifr_addr,
		    sizeof(ifrnetmask.lifr_addr));
		if (ioctl(fd, SIOCGLIFNETMASK, (char *)&ifrnetmask) < 0) {
			if (errno == EADDRNOTAVAIL) {
				/*
				 * Not available.
				 */
				netmask = NULL;
			} else {
				pcap_fmt_errmsg_for_errno(errbuf,
				    PCAP_ERRBUF_SIZE, errno,
				    "SIOCGLIFNETMASK: %.*s",
				    (int)sizeof(ifrnetmask.lifr_name),
				    ifrnetmask.lifr_name);
				ret = -1;
				break;
			}
		} else
			netmask = (struct sockaddr *)&ifrnetmask.lifr_addr;

		/*
		 * Get the broadcast address for this address on this
		 * interface (if any).
		 */
		if (ifrflags.lifr_flags & IFF_BROADCAST) {
			strncpy(ifrbroadaddr.lifr_name, ifrp->lifr_name,
			    sizeof(ifrbroadaddr.lifr_name));
			memcpy(&ifrbroadaddr.lifr_addr, &ifrp->lifr_addr,
			    sizeof(ifrbroadaddr.lifr_addr));
			if (ioctl(fd, SIOCGLIFBRDADDR,
			    (char *)&ifrbroadaddr) < 0) {
				if (errno == EADDRNOTAVAIL) {
					/*
					 * Not available.
					 */
					broadaddr = NULL;
				} else {
					pcap_fmt_errmsg_for_errno(errbuf,
					    PCAP_ERRBUF_SIZE, errno,
					    "SIOCGLIFBRDADDR: %.*s",
					    (int)sizeof(ifrbroadaddr.lifr_name),
					    ifrbroadaddr.lifr_name);
					ret = -1;
					break;
				}
			} else
				broadaddr = (struct sockaddr *)&ifrbroadaddr.lifr_broadaddr;
		} else {
			/*
			 * Not a broadcast interface, so no broadcast
			 * address.
			 */
			broadaddr = NULL;
		}

		/*
		 * Get the destination address for this address on this
		 * interface (if any).
		 */
		if (ifrflags.lifr_flags & IFF_POINTOPOINT) {
			strncpy(ifrdstaddr.lifr_name, ifrp->lifr_name,
			    sizeof(ifrdstaddr.lifr_name));
			memcpy(&ifrdstaddr.lifr_addr, &ifrp->lifr_addr,
			    sizeof(ifrdstaddr.lifr_addr));
			if (ioctl(fd, SIOCGLIFDSTADDR,
			    (char *)&ifrdstaddr) < 0) {
				if (errno == EADDRNOTAVAIL) {
					/*
					 * Not available.
					 */
					dstaddr = NULL;
				} else {
					pcap_fmt_errmsg_for_errno(errbuf,
					    PCAP_ERRBUF_SIZE, errno,
					    "SIOCGLIFDSTADDR: %.*s",
					    (int)sizeof(ifrdstaddr.lifr_name),
					    ifrdstaddr.lifr_name);
					ret = -1;
					break;
				}
			} else
				dstaddr = (struct sockaddr *)&ifrdstaddr.lifr_dstaddr;
		} else
			dstaddr = NULL;

#ifdef HAVE_SOLARIS
		/*
		 * If this entry has a colon followed by a number at
		 * the end, it's a logical interface.  Those are just
		 * the way you assign multiple IP addresses to a real
		 * interface, so an entry for a logical interface should
		 * be treated like the entry for the real interface;
		 * we do that by stripping off the ":" and the number.
		 */
		p = strchr(ifrp->lifr_name, ':');
		if (p != NULL) {
			/*
			 * We have a ":"; is it followed by a number?
			 */
			q = p + 1;
			while (isdigit((unsigned char)*q))
				q++;
			if (*q == '\0') {
				/*
				 * All digits after the ":" until the end.
				 * Strip off the ":" and everything after
				 * it.
				 */
				*p = '\0';
			}
		}
#endif

		/*
		 * Add information for this address to the list.
		 */
		if (add_addr_to_if(devlistp, ifrp->lifr_name,
		    ifrflags.lifr_flags, get_flags_func,
		    (struct sockaddr *)&ifrp->lifr_addr,
		    sizeof (struct sockaddr_storage),
		    netmask, sizeof (struct sockaddr_storage),
		    broadaddr, sizeof (struct sockaddr_storage),
		    dstaddr, sizeof (struct sockaddr_storage), errbuf) < 0) {
			ret = -1;
			break;
		}
	}
	free(buf);
	(void)close(fd6);
	(void)close(fd4);

	return (ret);
}