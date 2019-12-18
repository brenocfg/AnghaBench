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
typedef  scalar_t__ stats_op_t ;
typedef  scalar_t__ stats_ex_op_t ;
typedef  scalar_t__ setuserbuffer_op_t ;
typedef  scalar_t__ setmode_op_t ;
typedef  scalar_t__ setmintocopy_op_t ;
typedef  scalar_t__ setfilter_op_t ;
typedef  scalar_t__ setdirection_op_t ;
typedef  scalar_t__ setbuff_op_t ;
typedef  scalar_t__ set_datalink_op_t ;
typedef  scalar_t__ read_op_t ;
struct TYPE_3__ {int /*<<< orphan*/  oneshot_callback; int /*<<< orphan*/  cleanup_op; int /*<<< orphan*/  get_airpcap_handle_op; scalar_t__ live_dump_ended_op; scalar_t__ live_dump_op; scalar_t__ setuserbuffer_op; int /*<<< orphan*/  sendqueue_transmit_op; scalar_t__ oid_set_request_op; scalar_t__ oid_get_request_op; int /*<<< orphan*/  getevent_op; scalar_t__ setmintocopy_op; scalar_t__ setmode_op; scalar_t__ setbuff_op; scalar_t__ stats_ex_op; scalar_t__ stats_op; scalar_t__ getnonblock_op; scalar_t__ set_datalink_op; scalar_t__ setdirection_op; scalar_t__ setfilter_op; scalar_t__ inject_op; scalar_t__ read_op; } ;
typedef  TYPE_1__ pcap_t ;
typedef  scalar_t__ oid_set_request_op_t ;
typedef  scalar_t__ oid_get_request_op_t ;
typedef  scalar_t__ live_dump_op_t ;
typedef  scalar_t__ live_dump_ended_op_t ;
typedef  scalar_t__ inject_op_t ;
typedef  scalar_t__ getnonblock_op_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcap_cleanup_live_common ; 
 int /*<<< orphan*/  pcap_get_airpcap_handle_not_initialized ; 
 int /*<<< orphan*/  pcap_getevent_not_initialized ; 
 scalar_t__ pcap_not_initialized ; 
 scalar_t__ pcap_not_initialized_ptr ; 
 int /*<<< orphan*/  pcap_oneshot ; 
 int /*<<< orphan*/  pcap_sendqueue_transmit_not_initialized ; 

__attribute__((used)) static void
initialize_ops(pcap_t *p)
{
	/*
	 * Set operation pointers for operations that only work on
	 * an activated pcap_t to point to a routine that returns
	 * a "this isn't activated" error.
	 */
	p->read_op = (read_op_t)pcap_not_initialized;
	p->inject_op = (inject_op_t)pcap_not_initialized;
	p->setfilter_op = (setfilter_op_t)pcap_not_initialized;
	p->setdirection_op = (setdirection_op_t)pcap_not_initialized;
	p->set_datalink_op = (set_datalink_op_t)pcap_not_initialized;
	p->getnonblock_op = (getnonblock_op_t)pcap_not_initialized;
	p->stats_op = (stats_op_t)pcap_not_initialized;
#ifdef _WIN32
	p->stats_ex_op = (stats_ex_op_t)pcap_not_initialized_ptr;
	p->setbuff_op = (setbuff_op_t)pcap_not_initialized;
	p->setmode_op = (setmode_op_t)pcap_not_initialized;
	p->setmintocopy_op = (setmintocopy_op_t)pcap_not_initialized;
	p->getevent_op = pcap_getevent_not_initialized;
	p->oid_get_request_op = (oid_get_request_op_t)pcap_not_initialized;
	p->oid_set_request_op = (oid_set_request_op_t)pcap_not_initialized;
	p->sendqueue_transmit_op = pcap_sendqueue_transmit_not_initialized;
	p->setuserbuffer_op = (setuserbuffer_op_t)pcap_not_initialized;
	p->live_dump_op = (live_dump_op_t)pcap_not_initialized;
	p->live_dump_ended_op = (live_dump_ended_op_t)pcap_not_initialized;
	p->get_airpcap_handle_op = pcap_get_airpcap_handle_not_initialized;
#endif

	/*
	 * Default cleanup operation - implementations can override
	 * this, but should call pcap_cleanup_live_common() after
	 * doing their own additional cleanup.
	 */
	p->cleanup_op = pcap_cleanup_live_common;

	/*
	 * In most cases, the standard one-shot callback can
	 * be used for pcap_next()/pcap_next_ex().
	 */
	p->oneshot_callback = pcap_oneshot;
}