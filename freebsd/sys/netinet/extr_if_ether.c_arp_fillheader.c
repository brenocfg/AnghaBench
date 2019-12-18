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
struct if_encap_req {size_t bufsize; int /*<<< orphan*/  flags; struct if_encap_req* hdata; int /*<<< orphan*/  lladdr; int /*<<< orphan*/  family; int /*<<< orphan*/  rtype; struct if_encap_req* buf; } ;
typedef  struct if_encap_req u_char ;
struct ifnet {int (* if_requestencap ) (struct ifnet*,struct if_encap_req*) ;} ;
struct arphdr {int dummy; } ;
typedef  int /*<<< orphan*/  ereq ;

/* Variables and functions */
 int /*<<< orphan*/  AF_ARP ; 
 int /*<<< orphan*/  IFENCAP_FLAG_BROADCAST ; 
 int /*<<< orphan*/  IFENCAP_LL ; 
 int /*<<< orphan*/  ar_tha (struct arphdr*) ; 
 int /*<<< orphan*/  bzero (struct if_encap_req*,int) ; 
 int stub1 (struct ifnet*,struct if_encap_req*) ; 

__attribute__((used)) static int
arp_fillheader(struct ifnet *ifp, struct arphdr *ah, int bcast, u_char *buf,
    size_t *bufsize)
{
	struct if_encap_req ereq;
	int error;

	bzero(buf, *bufsize);
	bzero(&ereq, sizeof(ereq));
	ereq.buf = buf;
	ereq.bufsize = *bufsize;
	ereq.rtype = IFENCAP_LL;
	ereq.family = AF_ARP;
	ereq.lladdr = ar_tha(ah);
	ereq.hdata = (u_char *)ah;
	if (bcast)
		ereq.flags = IFENCAP_FLAG_BROADCAST;
	error = ifp->if_requestencap(ifp, &ereq);
	if (error == 0)
		*bufsize = ereq.bufsize;

	return (error);
}