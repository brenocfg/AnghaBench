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
struct ether_addr {int dummy; } ;
struct mac_range {struct ether_addr start; int /*<<< orphan*/  name; struct ether_addr end; } ;
struct TYPE_6__ {struct ether_addr* ether_dhost; struct ether_addr* ether_shost; } ;
struct TYPE_5__ {void* dst_mac_range; TYPE_1__* g; struct ether_addr* dst_mac; void* src_mac_range; struct ether_addr* src_mac; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_mac; int /*<<< orphan*/  src_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int /*<<< orphan*/ ,...) ; 
 void* atoi (scalar_t__) ; 
 int /*<<< orphan*/  bcopy (struct ether_addr*,struct ether_addr*,int) ; 
 TYPE_3__* eh ; 
 struct ether_addr* ether_aton (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ntoa (struct ether_addr*) ; 
 scalar_t__ index (int /*<<< orphan*/ ,char) ; 
 scalar_t__ p ; 
 TYPE_2__* targ ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
extract_mac_range(struct mac_range *r)
{
	struct ether_addr *e;
	if (verbose)
	    D("extract MAC range from %s", r->name);

	e = ether_aton(r->name);
	if (e == NULL) {
		D("invalid MAC address '%s'", r->name);
		return 1;
	}
	bcopy(e, &r->start, 6);
	bcopy(e, &r->end, 6);
#if 0
	bcopy(targ->src_mac, eh->ether_shost, 6);
	p = index(targ->g->src_mac, '-');
	if (p)
		targ->src_mac_range = atoi(p+1);

	bcopy(ether_aton(targ->g->dst_mac), targ->dst_mac, 6);
	bcopy(targ->dst_mac, eh->ether_dhost, 6);
	p = index(targ->g->dst_mac, '-');
	if (p)
		targ->dst_mac_range = atoi(p+1);
#endif
	if (verbose)
		D("%s starts at %s", r->name, ether_ntoa(&r->start));
	return 0;
}