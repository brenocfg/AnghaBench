#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  struct pcap_sf_pkthdr {int caplen; int /*<<< orphan*/  len; TYPE_1__ ts; } const pcap_sf_pkthdr ;
typedef  struct pcap_sf_pkthdr u_char ;
struct TYPE_4__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct pcap_pkthdr {int caplen; int /*<<< orphan*/  len; TYPE_2__ ts; } ;
typedef  int /*<<< orphan*/  sf_hdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (struct pcap_sf_pkthdr const*,int,int,int /*<<< orphan*/ *) ; 

void
pcap_dump(u_char *user, const struct pcap_pkthdr *h, const u_char *sp)
{
	register FILE *f;
	struct pcap_sf_pkthdr sf_hdr;

	f = (FILE *)user;
	sf_hdr.ts.tv_sec  = h->ts.tv_sec;
	sf_hdr.ts.tv_usec = h->ts.tv_usec;
	sf_hdr.caplen     = h->caplen;
	sf_hdr.len        = h->len;
	/* XXX we should check the return status */
	(void)fwrite(&sf_hdr, sizeof(sf_hdr), 1, f);
	(void)fwrite(sp, h->caplen, 1, f);
}