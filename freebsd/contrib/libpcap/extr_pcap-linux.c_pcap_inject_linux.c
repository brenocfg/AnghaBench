#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcap_linux {int ifindex; scalar_t__ cooked; int /*<<< orphan*/  sock_packet; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; struct pcap_linux* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int send (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcap_inject_linux(pcap_t *handle, const void *buf, size_t size)
{
	struct pcap_linux *handlep = handle->priv;
	int ret;

#ifdef HAVE_PF_PACKET_SOCKETS
	if (!handlep->sock_packet) {
		/* PF_PACKET socket */
		if (handlep->ifindex == -1) {
			/*
			 * We don't support sending on the "any" device.
			 */
			strlcpy(handle->errbuf,
			    "Sending packets isn't supported on the \"any\" device",
			    PCAP_ERRBUF_SIZE);
			return (-1);
		}

		if (handlep->cooked) {
			/*
			 * We don't support sending on the "any" device.
			 *
			 * XXX - how do you send on a bound cooked-mode
			 * socket?
			 * Is a "sendto()" required there?
			 */
			strlcpy(handle->errbuf,
			    "Sending packets isn't supported in cooked mode",
			    PCAP_ERRBUF_SIZE);
			return (-1);
		}
	}
#endif

	ret = send(handle->fd, buf, size, 0);
	if (ret == -1) {
		pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "send");
		return (-1);
	}
	return (ret);
}