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
typedef  int /*<<< orphan*/  u_char ;
struct pcap_dlpi {int /*<<< orphan*/  dlpi_hd; } ;
struct TYPE_4__ {int cc; size_t bufsize; int offset; int /*<<< orphan*/  errbuf; scalar_t__ buffer; scalar_t__ break_loop; int /*<<< orphan*/ * bp; struct pcap_dlpi* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  pcap_handler ;

/* Variables and functions */
 int DLPI_SUCCESS ; 
 int DL_SYSERR ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  dlpi_linkname (int /*<<< orphan*/ ) ; 
 int dlpi_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pcap_libdlpi_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int pcap_process_pkts (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pcap_read_libdlpi(pcap_t *p, int count, pcap_handler callback, u_char *user)
{
	struct pcap_dlpi *pd = p->priv;
	int len;
	u_char *bufp;
	size_t msglen;
	int retv;

	len = p->cc;
	if (len != 0) {
		bufp = p->bp;
		goto process_pkts;
	}
	do {
		/* Has "pcap_breakloop()" been called? */
		if (p->break_loop) {
			/*
			 * Yes - clear the flag that indicates that it has,
			 * and return -2 to indicate that we were told to
			 * break out of the loop.
			 */
			p->break_loop = 0;
			return (-2);
		}

		msglen = p->bufsize;
		bufp = (u_char *)p->buffer + p->offset;

		retv = dlpi_recv(pd->dlpi_hd, NULL, NULL, bufp,
		    &msglen, -1, NULL);
		if (retv != DLPI_SUCCESS) {
			/*
			 * This is most likely a call to terminate out of the
			 * loop. So, do not return an error message, instead
			 * check if "pcap_breakloop()" has been called above.
			 */
			if (retv == DL_SYSERR && errno == EINTR) {
				len = 0;
				continue;
			}
			pcap_libdlpi_err(dlpi_linkname(pd->dlpi_hd),
			    "dlpi_recv", retv, p->errbuf);
			return (-1);
		}
		len = msglen;
	} while (len == 0);

process_pkts:
	return (pcap_process_pkts(p, callback, user, count, bufp, len));
}