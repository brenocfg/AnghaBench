#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ pcap_t ;
typedef  scalar_t__ pcap_direction_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIOCSDIRECTION ; 
 int /*<<< orphan*/  BIOCSSEESENT ; 
 int BPF_D_IN ; 
 int BPF_D_INOUT ; 
 int BPF_D_OUT ; 
 scalar_t__ PCAP_D_IN ; 
 scalar_t__ PCAP_D_INOUT ; 
 scalar_t__ PCAP_D_OUT ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
pcap_setdirection_bpf(pcap_t *p, pcap_direction_t d)
{
#if defined(BIOCSDIRECTION)
	u_int direction;

	direction = (d == PCAP_D_IN) ? BPF_D_IN :
	    ((d == PCAP_D_OUT) ? BPF_D_OUT : BPF_D_INOUT);
	if (ioctl(p->fd, BIOCSDIRECTION, &direction) == -1) {
		pcap_fmt_errmsg_for_errno(p->errbuf, sizeof(p->errbuf),
		    errno, "Cannot set direction to %s",
		        (d == PCAP_D_IN) ? "PCAP_D_IN" :
			((d == PCAP_D_OUT) ? "PCAP_D_OUT" : "PCAP_D_INOUT"));
		return (-1);
	}
	return (0);
#elif defined(BIOCSSEESENT)
	u_int seesent;

	/*
	 * We don't support PCAP_D_OUT.
	 */
	if (d == PCAP_D_OUT) {
		pcap_snprintf(p->errbuf, sizeof(p->errbuf),
		    "Setting direction to PCAP_D_OUT is not supported on BPF");
		return -1;
	}

	seesent = (d == PCAP_D_INOUT);
	if (ioctl(p->fd, BIOCSSEESENT, &seesent) == -1) {
		pcap_fmt_errmsg_for_errno(p->errbuf, sizeof(p->errbuf),
		    errno, "Cannot set direction to %s",
		    (d == PCAP_D_INOUT) ? "PCAP_D_INOUT" : "PCAP_D_IN");
		return (-1);
	}
	return (0);
#else
	(void) pcap_snprintf(p->errbuf, sizeof(p->errbuf),
	    "This system doesn't support BIOCSSEESENT, so the direction can't be set");
	return (-1);
#endif
}