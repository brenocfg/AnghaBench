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
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int dummy; } ;
struct oneshot_userdata {TYPE_1__* pd; int /*<<< orphan*/  const** pkt; struct pcap_pkthdr* hdr; } ;
struct TYPE_5__ {int (* read_op ) (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  oneshot_callback; int /*<<< orphan*/ * rfile; struct pcap_pkthdr pcap_header; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int pcap_offline_read (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
pcap_next_ex(pcap_t *p, struct pcap_pkthdr **pkt_header,
    const u_char **pkt_data)
{
	struct oneshot_userdata s;

	s.hdr = &p->pcap_header;
	s.pkt = pkt_data;
	s.pd = p;

	/* Saves a pointer to the packet headers */
	*pkt_header= &p->pcap_header;

	if (p->rfile != NULL) {
		int status;

		/* We are on an offline capture */
		status = pcap_offline_read(p, 1, p->oneshot_callback,
		    (u_char *)&s);

		/*
		 * Return codes for pcap_offline_read() are:
		 *   -  0: EOF
		 *   - -1: error
		 *   - >1: OK
		 * The first one ('0') conflicts with the return code of
		 * 0 from pcap_read() meaning "no packets arrived before
		 * the timeout expired", so we map it to -2 so you can
		 * distinguish between an EOF from a savefile and a
		 * "no packets arrived before the timeout expired, try
		 * again" from a live capture.
		 */
		if (status == 0)
			return (-2);
		else
			return (status);
	}

	/*
	 * Return codes for pcap_read() are:
	 *   -  0: timeout
	 *   - -1: error
	 *   - -2: loop was broken out of with pcap_breakloop()
	 *   - >1: OK
	 * The first one ('0') conflicts with the return code of 0 from
	 * pcap_offline_read() meaning "end of file".
	*/
	return (p->read_op(p, 1, p->oneshot_callback, (u_char *)&s));
}