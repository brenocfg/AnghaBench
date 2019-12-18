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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {TYPE_1__* tcp; } ;
struct alias_link {TYPE_2__ data; } ;
struct ack_data_record {int active; int delta; int /*<<< orphan*/  ack_old; } ;
struct TYPE_3__ {struct ack_data_record* ack; } ;

/* Variables and functions */
 int N_LINK_TCP_DATA ; 
 int SeqDiff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
GetDeltaSeqOut(u_long seq, struct alias_link *lnk)
{
/*
Find out how much the sequence number has been altered for an outgoing
TCP packet.  To do this, a circular list of ACK numbers where the TCP
packet size was altered is searched.
*/

	int i;
	int delta, seq_diff_min;

	delta = 0;
	seq_diff_min = -1;
	for (i = 0; i < N_LINK_TCP_DATA; i++) {
		struct ack_data_record x;

		x = lnk->data.tcp->ack[i];
		if (x.active == 1) {
			int seq_diff;

			seq_diff = SeqDiff(x.ack_old, seq);
			if (seq_diff >= 0) {
				if (seq_diff_min >= 0) {
					if (seq_diff < seq_diff_min) {
						delta = x.delta;
						seq_diff_min = seq_diff;
					}
				} else {
					delta = x.delta;
					seq_diff_min = seq_diff;
				}
			}
		}
	}
	return (delta);
}