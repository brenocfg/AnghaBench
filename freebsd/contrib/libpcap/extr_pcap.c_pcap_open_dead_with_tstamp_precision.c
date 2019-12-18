#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_6__ {int tstamp_precision; } ;
struct TYPE_7__ {int snapshot; int linktype; int activated; scalar_t__ bpf_codegen_flags; int /*<<< orphan*/  cleanup_op; int /*<<< orphan*/  get_airpcap_handle_op; int /*<<< orphan*/  live_dump_ended_op; int /*<<< orphan*/  live_dump_op; int /*<<< orphan*/  setuserbuffer_op; int /*<<< orphan*/  sendqueue_transmit_op; int /*<<< orphan*/  oid_set_request_op; int /*<<< orphan*/  oid_get_request_op; int /*<<< orphan*/  getevent_op; int /*<<< orphan*/  setmintocopy_op; int /*<<< orphan*/  setmode_op; int /*<<< orphan*/  setbuff_op; int /*<<< orphan*/  stats_ex_op; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/  set_datalink_op; int /*<<< orphan*/  setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/  read_op; int /*<<< orphan*/  can_set_rfmon_op; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
#define  PCAP_TSTAMP_PRECISION_MICRO 129 
#define  PCAP_TSTAMP_PRECISION_NANO 128 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_can_set_rfmon_dead ; 
 int /*<<< orphan*/  pcap_cleanup_dead ; 
 int /*<<< orphan*/  pcap_get_airpcap_handle_dead ; 
 int /*<<< orphan*/  pcap_getevent_dead ; 
 int /*<<< orphan*/  pcap_getnonblock_dead ; 
 int /*<<< orphan*/  pcap_inject_dead ; 
 int /*<<< orphan*/  pcap_live_dump_dead ; 
 int /*<<< orphan*/  pcap_live_dump_ended_dead ; 
 int /*<<< orphan*/  pcap_oid_get_request_dead ; 
 int /*<<< orphan*/  pcap_oid_set_request_dead ; 
 int /*<<< orphan*/  pcap_read_dead ; 
 int /*<<< orphan*/  pcap_sendqueue_transmit_dead ; 
 int /*<<< orphan*/  pcap_set_datalink_dead ; 
 int /*<<< orphan*/  pcap_setbuff_dead ; 
 int /*<<< orphan*/  pcap_setdirection_dead ; 
 int /*<<< orphan*/  pcap_setfilter_dead ; 
 int /*<<< orphan*/  pcap_setmintocopy_dead ; 
 int /*<<< orphan*/  pcap_setmode_dead ; 
 int /*<<< orphan*/  pcap_setnonblock_dead ; 
 int /*<<< orphan*/  pcap_setuserbuffer_dead ; 
 int /*<<< orphan*/  pcap_stats_dead ; 
 int /*<<< orphan*/  pcap_stats_ex_dead ; 

pcap_t *
pcap_open_dead_with_tstamp_precision(int linktype, int snaplen, u_int precision)
{
	pcap_t *p;

	switch (precision) {

	case PCAP_TSTAMP_PRECISION_MICRO:
	case PCAP_TSTAMP_PRECISION_NANO:
		break;

	default:
		/*
		 * This doesn't really matter, but we don't have any way
		 * to report particular errors, so the only failure we
		 * should have is a memory allocation failure.  Just
		 * pick microsecond precision.
		 */
		precision = PCAP_TSTAMP_PRECISION_MICRO;
		break;
	}
	p = malloc(sizeof(*p));
	if (p == NULL)
		return NULL;
	memset (p, 0, sizeof(*p));
	p->snapshot = snaplen;
	p->linktype = linktype;
	p->opt.tstamp_precision = precision;
	p->can_set_rfmon_op = pcap_can_set_rfmon_dead;
	p->read_op = pcap_read_dead;
	p->inject_op = pcap_inject_dead;
	p->setfilter_op = pcap_setfilter_dead;
	p->setdirection_op = pcap_setdirection_dead;
	p->set_datalink_op = pcap_set_datalink_dead;
	p->getnonblock_op = pcap_getnonblock_dead;
	p->setnonblock_op = pcap_setnonblock_dead;
	p->stats_op = pcap_stats_dead;
#ifdef _WIN32
	p->stats_ex_op = pcap_stats_ex_dead;
	p->setbuff_op = pcap_setbuff_dead;
	p->setmode_op = pcap_setmode_dead;
	p->setmintocopy_op = pcap_setmintocopy_dead;
	p->getevent_op = pcap_getevent_dead;
	p->oid_get_request_op = pcap_oid_get_request_dead;
	p->oid_set_request_op = pcap_oid_set_request_dead;
	p->sendqueue_transmit_op = pcap_sendqueue_transmit_dead;
	p->setuserbuffer_op = pcap_setuserbuffer_dead;
	p->live_dump_op = pcap_live_dump_dead;
	p->live_dump_ended_op = pcap_live_dump_ended_dead;
	p->get_airpcap_handle_op = pcap_get_airpcap_handle_dead;
#endif
	p->cleanup_op = pcap_cleanup_dead;

	/*
	 * A "dead" pcap_t never requires special BPF code generation.
	 */
	p->bpf_codegen_flags = 0;

	p->activated = 1;
	return (p);
}