#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* tv_usec; void* tv_sec; } ;
typedef  struct pcap_sf_pkthdr {int caplen; int /*<<< orphan*/  len; TYPE_1__ ts; } const pcap_sf_pkthdr ;
typedef  struct pcap_sf_pkthdr u_char ;
struct pcap_pkthdr {int caplen; int /*<<< orphan*/  len; TYPE_1__ ts; } ;
typedef  int /*<<< orphan*/  sh ;
typedef  void* bpf_int32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 size_t bufleft ; 
 int /*<<< orphan*/  bufpkt ; 
 scalar_t__ bufpos ; 
 scalar_t__ cur_snaplen ; 
 int /*<<< orphan*/  dump_packet_nobuf (struct pcap_sf_pkthdr*,struct pcap_sf_pkthdr const*,struct pcap_sf_pkthdr const*) ; 
 scalar_t__ flush_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct pcap_sf_pkthdr const*,int) ; 
 int /*<<< orphan*/  packets_dropped ; 
 int /*<<< orphan*/  snaplen ; 
 scalar_t__ suspended ; 

void
dump_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *sp)
{
	FILE *f = (FILE *)user;
#ifdef __FreeBSD__
	struct pcap_sf_pkthdr sh;
	size_t len = sizeof(sh) + h->caplen;
#else
	size_t len = sizeof(*h) + h->caplen;
#endif

	if (len < sizeof(*h) || h->caplen > (size_t)cur_snaplen) {
		logmsg(LOG_NOTICE, "invalid size %u (%u/%u), packet dropped",
		       len, cur_snaplen, snaplen);
		packets_dropped++;
		return;
	}

	if (len <= bufleft)
		goto append;

	if (suspended) {
		packets_dropped++;
		return;
	}

	if (flush_buffer(f)) {
		packets_dropped++;
		return;
	}

	if (len > bufleft) {
		dump_packet_nobuf(user, h, sp);
		return;
	}

 append:       
#ifdef __FreeBSD__
	sh.ts.tv_sec = (bpf_int32)h->ts.tv_sec;
	sh.ts.tv_usec = (bpf_int32)h->ts.tv_usec;
	sh.caplen = h->caplen;
	sh.len = h->len;

	memcpy(bufpos, &sh, sizeof(sh));
	memcpy(bufpos + sizeof(sh), sp, h->caplen);
#else
	memcpy(bufpos, h, sizeof(*h));
	memcpy(bufpos + sizeof(*h), sp, h->caplen);
#endif

	bufpos += len;
	bufleft -= len;
	bufpkt++;

	return;
}