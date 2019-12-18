#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_file_header {int thiszone; int snaplen; int linktype; scalar_t__ sigfigs; int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; int /*<<< orphan*/  magic; } ;
struct TYPE_4__ {scalar_t__ tstamp_precision; } ;
struct TYPE_5__ {TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_TCPDUMP_MAGIC ; 
 scalar_t__ PCAP_TSTAMP_PRECISION_NANO ; 
 int /*<<< orphan*/  PCAP_VERSION_MAJOR ; 
 int /*<<< orphan*/  PCAP_VERSION_MINOR ; 
 int /*<<< orphan*/  TCPDUMP_MAGIC ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sf_write_header(pcap_t *p, FILE *fp, int linktype, int thiszone, int snaplen)
{
	struct pcap_file_header hdr;

	hdr.magic = p->opt.tstamp_precision == PCAP_TSTAMP_PRECISION_NANO ? NSEC_TCPDUMP_MAGIC : TCPDUMP_MAGIC;
	hdr.version_major = PCAP_VERSION_MAJOR;
	hdr.version_minor = PCAP_VERSION_MINOR;

	hdr.thiszone = thiszone;
	hdr.snaplen = snaplen;
	hdr.sigfigs = 0;
	hdr.linktype = linktype;

	if (fwrite((char *)&hdr, sizeof(hdr), 1, fp) != 1)
		return (-1);

	return (0);
}