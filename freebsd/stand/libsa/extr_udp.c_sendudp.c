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
struct udpiphdr {int /*<<< orphan*/  ui_dst; int /*<<< orphan*/  ui_src; int /*<<< orphan*/  ui_len; int /*<<< orphan*/  ui_pr; } ;
struct udphdr {int /*<<< orphan*/  uh_sum; int /*<<< orphan*/  uh_ulen; int /*<<< orphan*/  uh_dport; int /*<<< orphan*/  uh_sport; } ;
struct ip {int dummy; } ;
struct iodesc {int /*<<< orphan*/  destip; int /*<<< orphan*/  myip; int /*<<< orphan*/  destport; int /*<<< orphan*/  myport; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  bzero (struct udpiphdr*,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int /*<<< orphan*/  in_cksum (struct udpiphdr*,size_t) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sendip (struct iodesc*,struct udphdr*,size_t,int /*<<< orphan*/ ) ; 

ssize_t
sendudp(struct iodesc *d, void *pkt, size_t len)
{
	ssize_t cc;
	struct udpiphdr *ui;
	struct udphdr *uh;

#ifdef NET_DEBUG
 	if (debug) {
		printf("sendudp: d=%lx called.\n", (long)d);
		if (d) {
			printf("saddr: %s:%d",
			    inet_ntoa(d->myip), ntohs(d->myport));
			printf(" daddr: %s:%d\n",
			    inet_ntoa(d->destip), ntohs(d->destport));
		}
	}
#endif

	ui = (struct udpiphdr *)pkt - 1;
	bzero(ui, sizeof(*ui));

	uh = (struct udphdr *)pkt - 1;
	len += sizeof(*uh);

	uh->uh_sport = d->myport;
	uh->uh_dport = d->destport;
	uh->uh_ulen = htons(len);

	ui->ui_pr = IPPROTO_UDP;
	ui->ui_len = uh->uh_ulen;
	ui->ui_src = d->myip;
	ui->ui_dst = d->destip;

#ifndef UDP_NO_CKSUM
	uh->uh_sum = in_cksum(ui, len + sizeof (struct ip));
#endif

	cc = sendip(d, uh, len, IPPROTO_UDP);
	if (cc == -1)
		return (-1);
	if (cc != len)
		panic("sendudp: bad write (%zd != %zd)", cc, len);
	return (cc - sizeof(*uh));
}