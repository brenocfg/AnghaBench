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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct if_info {int /*<<< orphan*/  ii_ifname; int /*<<< orphan*/  ii_fd; int /*<<< orphan*/  ii_ipaddr; scalar_t__ ii_eaddr; } ;
struct ether_header {int /*<<< orphan*/  ether_shost; int /*<<< orphan*/  ether_dhost; int /*<<< orphan*/  ether_type; } ;
struct ether_arp {int /*<<< orphan*/  arp_tha; scalar_t__ arp_spa; scalar_t__ arp_tpa; int /*<<< orphan*/  arp_sha; int /*<<< orphan*/  arp_op; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_REVARP ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  REVARP_REPLY ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,scalar_t__) ; 
 int /*<<< orphan*/  eatoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_arptab (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
rarp_reply(struct if_info *ii, struct ether_header *ep, in_addr_t ipaddr,
		u_int len)
{
	u_int n;
	struct ether_arp *ap = (struct ether_arp *)(ep + 1);

	update_arptab((u_char *)&ap->arp_sha, ipaddr);

	/*
	 * Build the rarp reply by modifying the rarp request in place.
	 */
	ap->arp_op = htons(REVARP_REPLY);

#ifdef BROKEN_BPF
	ep->ether_type = ETHERTYPE_REVARP;
#endif
	bcopy((char *)&ap->arp_sha, (char *)&ep->ether_dhost, 6);
	bcopy((char *)ii->ii_eaddr, (char *)&ep->ether_shost, 6);
	bcopy((char *)ii->ii_eaddr, (char *)&ap->arp_sha, 6);

	bcopy((char *)&ipaddr, (char *)ap->arp_tpa, 4);
	/* Target hardware is unchanged. */
	bcopy((char *)&ii->ii_ipaddr, (char *)ap->arp_spa, 4);

	/* Zero possible garbage after packet. */
	bzero((char *)ep + (sizeof(*ep) + sizeof(*ap)),
			len - (sizeof(*ep) + sizeof(*ap)));
	n = write(ii->ii_fd, (char *)ep, len);
	if (n != len)
		logmsg(LOG_ERR, "write: only %d of %d bytes written", n, len);
	if (verbose)
		logmsg(LOG_INFO, "%s %s at %s REPLIED", ii->ii_ifname,
		    eatoa(ap->arp_tha),
		    intoa(ntohl(ipaddr)));
}