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
typedef  int /*<<< orphan*/  time_t ;
struct udpiphdr {scalar_t__ ui_len; int /*<<< orphan*/  ui_x1; } ;
struct udphdr {scalar_t__ uh_ulen; scalar_t__ uh_dport; scalar_t__ uh_sum; } ;
struct ip {int dummy; } ;
struct iodesc {scalar_t__ myport; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ in_cksum (struct udpiphdr*,int) ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int readip (struct iodesc*,void**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t
readudp(struct iodesc *d, void **pkt, void **payload, time_t tleft)
{
	ssize_t n;
	struct udphdr *uh;
	void *ptr;

#ifdef NET_DEBUG
	if (debug)
		printf("readudp: called\n");
#endif

	uh = NULL;
	ptr = NULL;
	n = readip(d, &ptr, (void **)&uh, tleft, IPPROTO_UDP);
	if (n == -1 || n < sizeof(*uh) || n != ntohs(uh->uh_ulen)) {
		free(ptr);
		return (-1);
	}

	if (uh->uh_dport != d->myport) {
#ifdef NET_DEBUG
		if (debug)
			printf("readudp: bad dport %d != %d\n",
				d->myport, ntohs(uh->uh_dport));
#endif
		free(ptr);
		return (-1);
	}

#ifndef UDP_NO_CKSUM
	if (uh->uh_sum) {
		struct udpiphdr *ui;
		struct ip *ip;
		struct ip tip;

		n = ntohs(uh->uh_ulen) + sizeof(*ip);

		/* Check checksum (must save and restore ip header) */
		ip = (struct ip *)uh - 1;
		tip = *ip;
		ui = (struct udpiphdr *)ip;
		bzero(&ui->ui_x1, sizeof(ui->ui_x1));
		ui->ui_len = uh->uh_ulen;
		if (in_cksum(ui, n) != 0) {
#ifdef NET_DEBUG
			if (debug)
				printf("readudp: bad cksum\n");
#endif
			free(ptr);
			return (-1);
		}
		*ip = tip;
	}
#endif
	if (ntohs(uh->uh_ulen) < sizeof(*uh)) {
#ifdef NET_DEBUG
		if (debug)
			printf("readudp: bad udp len %d < %d\n",
				ntohs(uh->uh_ulen), (int)sizeof(*uh));
#endif
		free(ptr);
		return (-1);
	}

	n = (n > (ntohs(uh->uh_ulen) - sizeof(*uh))) ? 
	    ntohs(uh->uh_ulen) - sizeof(*uh) : n;
	*pkt = ptr;
	*payload = (void *)((uintptr_t)uh + sizeof(*uh));
	return (n);
}