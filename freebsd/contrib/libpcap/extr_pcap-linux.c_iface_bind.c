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
struct sockaddr_ll {int sll_ifindex; int sll_protocol; int /*<<< orphan*/  sll_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sll ;
typedef  int /*<<< orphan*/  err ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_IFACE_NOT_UP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int bind (int,struct sockaddr*,int) ; 
 int errno ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_ll*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
iface_bind(int fd, int ifindex, char *ebuf, int protocol)
{
	struct sockaddr_ll	sll;
	int			err;
	socklen_t		errlen = sizeof(err);

	memset(&sll, 0, sizeof(sll));
	sll.sll_family		= AF_PACKET;
	sll.sll_ifindex		= ifindex;
	sll.sll_protocol	= protocol;

	if (bind(fd, (struct sockaddr *) &sll, sizeof(sll)) == -1) {
		if (errno == ENETDOWN) {
			/*
			 * Return a "network down" indication, so that
			 * the application can report that rather than
			 * saying we had a mysterious failure and
			 * suggest that they report a problem to the
			 * libpcap developers.
			 */
			return PCAP_ERROR_IFACE_NOT_UP;
		} else {
			pcap_fmt_errmsg_for_errno(ebuf, PCAP_ERRBUF_SIZE,
			    errno, "bind");
			return PCAP_ERROR;
		}
	}

	/* Any pending errors, e.g., network is down? */

	if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
		pcap_fmt_errmsg_for_errno(ebuf, PCAP_ERRBUF_SIZE,
		    errno, "getsockopt");
		return 0;
	}

	if (err == ENETDOWN) {
		/*
		 * Return a "network down" indication, so that
		 * the application can report that rather than
		 * saying we had a mysterious failure and
		 * suggest that they report a problem to the
		 * libpcap developers.
		 */
		return PCAP_ERROR_IFACE_NOT_UP;
	} else if (err > 0) {
		pcap_fmt_errmsg_for_errno(ebuf, PCAP_ERRBUF_SIZE,
		    err, "bind");
		return 0;
	}

	return 1;
}