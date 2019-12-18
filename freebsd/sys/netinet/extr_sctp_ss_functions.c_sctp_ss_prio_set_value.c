#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct sctp_tcb {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  priority; } ;
struct TYPE_4__ {TYPE_1__ prio; } ;
struct sctp_stream_out {TYPE_2__ ss_params; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_ss_prio_add (struct sctp_tcb*,struct sctp_association*,struct sctp_stream_out*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctp_ss_prio_remove (struct sctp_tcb*,struct sctp_association*,struct sctp_stream_out*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
sctp_ss_prio_set_value(struct sctp_tcb *stcb, struct sctp_association *asoc,
    struct sctp_stream_out *strq, uint16_t value)
{
	if (strq == NULL) {
		return (-1);
	}
	strq->ss_params.prio.priority = value;
	sctp_ss_prio_remove(stcb, asoc, strq, NULL, 1);
	sctp_ss_prio_add(stcb, asoc, strq, NULL, 1);
	return (1);
}