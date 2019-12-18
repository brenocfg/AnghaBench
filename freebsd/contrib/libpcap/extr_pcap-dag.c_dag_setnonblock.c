#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct pcap_dag {int /*<<< orphan*/  dag_flags; int /*<<< orphan*/  dag_stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; struct pcap_dag* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int dag_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DAGF_NONBLOCK ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ dag_get_stream_poll64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct timeval*,struct timeval*) ; 
 scalar_t__ dag_set_stream_poll64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pcap_setnonblock_fd (TYPE_1__*,int) ; 

__attribute__((used)) static int
dag_setnonblock(pcap_t *p, int nonblock)
{
	struct pcap_dag *pd = p->priv;
	dag_size_t mindata;
	struct timeval maxwait;
	struct timeval poll;

	/*
	 * Set non-blocking mode on the FD.
	 * XXX - is that necessary?  If not, don't bother calling it,
	 * and have a "dag_getnonblock()" function that looks at
	 * "pd->dag_flags".
	 */
	if (pcap_setnonblock_fd(p, nonblock) < 0)
		return (-1);

	if (dag_get_stream_poll64(p->fd, pd->dag_stream,
				&mindata, &maxwait, &poll) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "dag_get_stream_poll");
		return -1;
	}

	/* Amount of data to collect in Bytes before calling callbacks.
	 * Important for efficiency, but can introduce latency
	 * at low packet rates if to_ms not set!
	 */
	if(nonblock)
		mindata = 0;
	else
		mindata = 65536;

	if (dag_set_stream_poll64(p->fd, pd->dag_stream,
				mindata, &maxwait, &poll) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "dag_set_stream_poll");
		return -1;
	}

	if (nonblock) {
		pd->dag_flags |= DAGF_NONBLOCK;
	} else {
		pd->dag_flags &= ~DAGF_NONBLOCK;
	}
	return (0);
}