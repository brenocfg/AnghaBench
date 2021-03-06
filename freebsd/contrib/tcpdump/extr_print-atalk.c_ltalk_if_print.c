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
struct pcap_pkthdr {scalar_t__ caplen; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ llap_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

u_int
ltalk_if_print(netdissect_options *ndo,
               const struct pcap_pkthdr *h, const u_char *p)
{
	u_int hdrlen;

	hdrlen = llap_print(ndo, p, h->len);
	if (hdrlen == 0) {
		/* Cut short by the snapshot length. */
		return (h->caplen);
	}
	return (hdrlen);
}