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
typedef  int /*<<< orphan*/  zero ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  timeout ;
struct timeval {int tv_sec; int tv_usec; } ;
struct strioctl {int ic_len; char* ic_dp; int /*<<< orphan*/  ic_cmd; int /*<<< orphan*/  ic_timout; } ;
struct TYPE_4__ {int timeout; scalar_t__ promisc; scalar_t__ immediate; } ;
struct TYPE_5__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  flags ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  INFTIM ; 
 int /*<<< orphan*/  I_STR ; 
 int /*<<< orphan*/  NIOCSCHUNK ; 
 int /*<<< orphan*/  NIOCSFLAGS ; 
 int /*<<< orphan*/  NIOCSTIME ; 
 int NI_DROPS ; 
 int NI_LEN ; 
 int NI_PROMISC ; 
 int NI_TIMESTAMP ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
nit_setflags(pcap_t *p)
{
	bpf_u_int32 flags;
	struct strioctl si;
	u_int zero = 0;
	struct timeval timeout;

	if (p->opt.immediate) {
		/*
		 * Set the chunk size to zero, so that chunks get sent
		 * up immediately.
		 */
		si.ic_cmd = NIOCSCHUNK;
		si.ic_len = sizeof(zero);
		si.ic_dp = (char *)&zero;
		if (ioctl(p->fd, I_STR, (char *)&si) < 0) {
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "NIOCSCHUNK");
			return (-1);
		}
	}
	si.ic_timout = INFTIM;
	if (p->opt.timeout != 0) {
		timeout.tv_sec = p->opt.timeout / 1000;
		timeout.tv_usec = (p->opt.timeout * 1000) % 1000000;
		si.ic_cmd = NIOCSTIME;
		si.ic_len = sizeof(timeout);
		si.ic_dp = (char *)&timeout;
		if (ioctl(p->fd, I_STR, (char *)&si) < 0) {
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "NIOCSTIME");
			return (-1);
		}
	}
	flags = NI_TIMESTAMP | NI_LEN | NI_DROPS;
	if (p->opt.promisc)
		flags |= NI_PROMISC;
	si.ic_cmd = NIOCSFLAGS;
	si.ic_len = sizeof(flags);
	si.ic_dp = (char *)&flags;
	if (ioctl(p->fd, I_STR, (char *)&si) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "NIOCSFLAGS");
		return (-1);
	}
	return (0);
}