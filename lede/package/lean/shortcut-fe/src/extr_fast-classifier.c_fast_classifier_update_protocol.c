#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sfe_connection_create {int protocol; int /*<<< orphan*/  dest_port; int /*<<< orphan*/  dest_ip; int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_ip; int /*<<< orphan*/  flags; int /*<<< orphan*/  dest_td_max_end; int /*<<< orphan*/  dest_td_end; int /*<<< orphan*/  dest_td_max_window; int /*<<< orphan*/  dest_td_window_scale; int /*<<< orphan*/  src_td_max_end; int /*<<< orphan*/  src_td_end; int /*<<< orphan*/  src_td_max_window; int /*<<< orphan*/  src_td_window_scale; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; TYPE_1__* seen; } ;
struct TYPE_6__ {TYPE_2__ tcp; } ;
struct nf_conn {int /*<<< orphan*/  lock; TYPE_3__ proto; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  td_maxend; int /*<<< orphan*/  td_end; int /*<<< orphan*/  td_maxwin; int /*<<< orphan*/  td_scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TRACE (char*,int,...) ; 
 int /*<<< orphan*/  FAST_CL_EXCEPTION_TCP_NOT_ESTABLISHED ; 
 int /*<<< orphan*/  FAST_CL_EXCEPTION_UNKNOW_PROTOCOL ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int IP_CT_TCP_FLAG_BE_LIBERAL ; 
 int /*<<< orphan*/  SFE_CREATE_FLAG_NO_SEQ_CHECK ; 
 int /*<<< orphan*/  TCP_CONNTRACK_ESTABLISHED ; 
 int /*<<< orphan*/  fast_classifier_incr_exceptions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_tcp_no_window_check ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fast_classifier_update_protocol(struct sfe_connection_create *p_sic, struct nf_conn *ct)
{
	switch (p_sic->protocol) {
	case IPPROTO_TCP:
		p_sic->src_td_window_scale = ct->proto.tcp.seen[0].td_scale;
		p_sic->src_td_max_window = ct->proto.tcp.seen[0].td_maxwin;
		p_sic->src_td_end = ct->proto.tcp.seen[0].td_end;
		p_sic->src_td_max_end = ct->proto.tcp.seen[0].td_maxend;
		p_sic->dest_td_window_scale = ct->proto.tcp.seen[1].td_scale;
		p_sic->dest_td_max_window = ct->proto.tcp.seen[1].td_maxwin;
		p_sic->dest_td_end = ct->proto.tcp.seen[1].td_end;
		p_sic->dest_td_max_end = ct->proto.tcp.seen[1].td_maxend;

		if (nf_ct_tcp_no_window_check
		    || (ct->proto.tcp.seen[0].flags & IP_CT_TCP_FLAG_BE_LIBERAL)
		    || (ct->proto.tcp.seen[1].flags & IP_CT_TCP_FLAG_BE_LIBERAL)) {
			p_sic->flags |= SFE_CREATE_FLAG_NO_SEQ_CHECK;
		}

		/*
		 * If the connection is shutting down do not manage it.
		 * state can not be SYN_SENT, SYN_RECV because connection is assured
		 * Not managed states: FIN_WAIT, CLOSE_WAIT, LAST_ACK, TIME_WAIT, CLOSE.
		 */
		spin_lock_bh(&ct->lock);
		if (ct->proto.tcp.state != TCP_CONNTRACK_ESTABLISHED) {
			spin_unlock_bh(&ct->lock);
			fast_classifier_incr_exceptions(FAST_CL_EXCEPTION_TCP_NOT_ESTABLISHED);
			DEBUG_TRACE("connection in termination state: %#x, s: %pI4:%u, d: %pI4:%u\n",
				    ct->proto.tcp.state, &p_sic->src_ip, ntohs(p_sic->src_port),
				    &p_sic->dest_ip, ntohs(p_sic->dest_port));
			return 0;
		}
		spin_unlock_bh(&ct->lock);
		break;

	case IPPROTO_UDP:
		break;

	default:
		fast_classifier_incr_exceptions(FAST_CL_EXCEPTION_UNKNOW_PROTOCOL);
		DEBUG_TRACE("unhandled protocol %d\n", p_sic->protocol);
		return 0;
	}

	return 1;
}