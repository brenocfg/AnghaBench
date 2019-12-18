#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tv_sec; int tv_usec; } ;
struct nit_ioc {int nioc_bufalign; scalar_t__ nioc_bufspace; int /*<<< orphan*/  nioc_flags; TYPE_1__ nioc_timeout; scalar_t__ nioc_chunksize; scalar_t__ nioc_bufoffset; int /*<<< orphan*/  nioc_snaplen; int /*<<< orphan*/  nioc_typetomatch; } ;
struct TYPE_6__ {scalar_t__ buffer_size; int timeout; scalar_t__ promisc; scalar_t__ immediate; } ;
struct TYPE_7__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; TYPE_2__ opt; int /*<<< orphan*/  snapshot; } ;
typedef  TYPE_3__ pcap_t ;
typedef  int /*<<< orphan*/  nioc ;

/* Variables and functions */
 scalar_t__ BUFSPACE ; 
 scalar_t__ CHUNKSIZE ; 
 int /*<<< orphan*/  NF_PROMISC ; 
 int /*<<< orphan*/  NF_TIMEOUT ; 
 int /*<<< orphan*/  NT_ALLTYPES ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  SIOCSNIT ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nit_ioc*) ; 
 int /*<<< orphan*/  memset (struct nit_ioc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
nit_setflags(pcap_t *p)
{
	struct nit_ioc nioc;

	memset(&nioc, 0, sizeof(nioc));
	nioc.nioc_typetomatch = NT_ALLTYPES;
	nioc.nioc_snaplen = p->snapshot;
	nioc.nioc_bufalign = sizeof(int);
	nioc.nioc_bufoffset = 0;

	if (p->opt.buffer_size != 0)
		nioc.nioc_bufspace = p->opt.buffer_size;
	else {
		/* Default buffer size */
		nioc.nioc_bufspace = BUFSPACE;
	}

	if (p->opt.immediate) {
		/*
		 * XXX - will this cause packets to be delivered immediately?
		 * XXX - given that this is for SunOS prior to 4.0, do
		 * we care?
		 */
		nioc.nioc_chunksize = 0;
	} else
		nioc.nioc_chunksize = CHUNKSIZE;
	if (p->opt.timeout != 0) {
		nioc.nioc_flags |= NF_TIMEOUT;
		nioc.nioc_timeout.tv_sec = p->opt.timeout / 1000;
		nioc.nioc_timeout.tv_usec = (p->opt.timeout * 1000) % 1000000;
	}
	if (p->opt.promisc)
		nioc.nioc_flags |= NF_PROMISC;

	if (ioctl(p->fd, SIOCSNIT, &nioc) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "SIOCSNIT");
		return (-1);
	}
	return (0);
}