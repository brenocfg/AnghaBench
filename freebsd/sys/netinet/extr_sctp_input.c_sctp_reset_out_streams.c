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
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_4__ {size_t streamoutcnt; TYPE_1__* strmout; } ;
struct sctp_tcb {TYPE_2__ asoc; } ;
struct TYPE_3__ {scalar_t__ next_mid_unordered; scalar_t__ next_mid_ordered; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_NOTIFY_STR_RESET_SEND ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 size_t ntohs (size_t) ; 
 int /*<<< orphan*/  sctp_ulp_notify (int /*<<< orphan*/ ,struct sctp_tcb*,scalar_t__,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sctp_reset_out_streams(struct sctp_tcb *stcb, uint32_t number_entries, uint16_t *list)
{
	uint32_t i;
	uint16_t temp;

	if (number_entries > 0) {
		for (i = 0; i < number_entries; i++) {
			temp = ntohs(list[i]);
			if (temp >= stcb->asoc.streamoutcnt) {
				/* no such stream */
				continue;
			}
			stcb->asoc.strmout[temp].next_mid_ordered = 0;
			stcb->asoc.strmout[temp].next_mid_unordered = 0;
		}
	} else {
		for (i = 0; i < stcb->asoc.streamoutcnt; i++) {
			stcb->asoc.strmout[i].next_mid_ordered = 0;
			stcb->asoc.strmout[i].next_mid_unordered = 0;
		}
	}
	sctp_ulp_notify(SCTP_NOTIFY_STR_RESET_SEND, stcb, number_entries, (void *)list, SCTP_SO_NOT_LOCKED);
}