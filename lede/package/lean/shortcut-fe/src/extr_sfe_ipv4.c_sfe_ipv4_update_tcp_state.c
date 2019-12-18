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
struct sfe_ipv4_tcp_connection_match {scalar_t__ max_win; scalar_t__ max_end; scalar_t__ end; } ;
struct TYPE_2__ {struct sfe_ipv4_tcp_connection_match tcp; } ;
struct sfe_ipv4_connection_match {int /*<<< orphan*/  flags; TYPE_1__ protocol_state; } ;
struct sfe_ipv4_connection {struct sfe_ipv4_connection_match* reply_match; struct sfe_ipv4_connection_match* original_match; } ;
struct sfe_connection_create {scalar_t__ src_td_max_window; scalar_t__ dest_td_max_window; int flags; scalar_t__ dest_td_max_end; scalar_t__ dest_td_end; scalar_t__ src_td_max_end; scalar_t__ src_td_end; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int SFE_CREATE_FLAG_NO_SEQ_CHECK ; 
 int /*<<< orphan*/  SFE_IPV4_CONNECTION_MATCH_FLAG_NO_SEQ_CHECK ; 

__attribute__((used)) static void
sfe_ipv4_update_tcp_state(struct sfe_ipv4_connection *c,
			  struct sfe_connection_create *sic)
{
	struct sfe_ipv4_connection_match *orig_cm;
	struct sfe_ipv4_connection_match *repl_cm;
	struct sfe_ipv4_tcp_connection_match *orig_tcp;
	struct sfe_ipv4_tcp_connection_match *repl_tcp;

	orig_cm = c->original_match;
	repl_cm = c->reply_match;
	orig_tcp = &orig_cm->protocol_state.tcp;
	repl_tcp = &repl_cm->protocol_state.tcp;

	/* update orig */
	if (orig_tcp->max_win < sic->src_td_max_window) {
		orig_tcp->max_win = sic->src_td_max_window;
	}
	if ((s32)(orig_tcp->end - sic->src_td_end) < 0) {
		orig_tcp->end = sic->src_td_end;
	}
	if ((s32)(orig_tcp->max_end - sic->src_td_max_end) < 0) {
		orig_tcp->max_end = sic->src_td_max_end;
	}

	/* update reply */
	if (repl_tcp->max_win < sic->dest_td_max_window) {
		repl_tcp->max_win = sic->dest_td_max_window;
	}
	if ((s32)(repl_tcp->end - sic->dest_td_end) < 0) {
		repl_tcp->end = sic->dest_td_end;
	}
	if ((s32)(repl_tcp->max_end - sic->dest_td_max_end) < 0) {
		repl_tcp->max_end = sic->dest_td_max_end;
	}

	/* update match flags */
	orig_cm->flags &= ~SFE_IPV4_CONNECTION_MATCH_FLAG_NO_SEQ_CHECK;
	repl_cm->flags &= ~SFE_IPV4_CONNECTION_MATCH_FLAG_NO_SEQ_CHECK;
	if (sic->flags & SFE_CREATE_FLAG_NO_SEQ_CHECK) {
		orig_cm->flags |= SFE_IPV4_CONNECTION_MATCH_FLAG_NO_SEQ_CHECK;
		repl_cm->flags |= SFE_IPV4_CONNECTION_MATCH_FLAG_NO_SEQ_CHECK;
	}
}