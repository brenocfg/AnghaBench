#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ipN_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

u_int
raw_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, const u_char *p)
{
	if (ndo->ndo_eflag)
		ND_PRINT((ndo, "ip: "));

	ipN_print(ndo, p, h->len);

	return (0);
}