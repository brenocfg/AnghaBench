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
struct sctp_queued_to_read {int fsn_included; int /*<<< orphan*/  port_from; int /*<<< orphan*/  stcb; TYPE_1__* whoFrom; int /*<<< orphan*/  sinfo_assoc_id; int /*<<< orphan*/  sinfo_cumtsn; int /*<<< orphan*/  sinfo_tsn; int /*<<< orphan*/  sinfo_context; int /*<<< orphan*/  sinfo_ppid; int /*<<< orphan*/  sinfo_flags; int /*<<< orphan*/  mid; int /*<<< orphan*/  top_fsn; int /*<<< orphan*/  reasm; int /*<<< orphan*/  sinfo_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sctp_queued_to_read*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sctp_build_readq_entry_from_ctl(struct sctp_queued_to_read *nc, struct sctp_queued_to_read *control)
{
	memset(nc, 0, sizeof(struct sctp_queued_to_read));
	nc->sinfo_stream = control->sinfo_stream;
	nc->mid = control->mid;
	TAILQ_INIT(&nc->reasm);
	nc->top_fsn = control->top_fsn;
	nc->mid = control->mid;
	nc->sinfo_flags = control->sinfo_flags;
	nc->sinfo_ppid = control->sinfo_ppid;
	nc->sinfo_context = control->sinfo_context;
	nc->fsn_included = 0xffffffff;
	nc->sinfo_tsn = control->sinfo_tsn;
	nc->sinfo_cumtsn = control->sinfo_cumtsn;
	nc->sinfo_assoc_id = control->sinfo_assoc_id;
	nc->whoFrom = control->whoFrom;
	atomic_add_int(&nc->whoFrom->ref_count, 1);
	nc->stcb = control->stcb;
	nc->port_from = control->port_from;
}