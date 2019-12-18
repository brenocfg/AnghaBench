#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sctp_queued_to_read {scalar_t__ on_read_q; int /*<<< orphan*/  fsn_included; } ;
struct sctp_inpcb {int /*<<< orphan*/  read_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sctp_queued_to_read*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
sctp_reset_a_control(struct sctp_queued_to_read *control,
    struct sctp_inpcb *inp, uint32_t tsn)
{
	control->fsn_included = tsn;
	if (control->on_read_q) {
		/*
		 * We have to purge it from there, hopefully this will work
		 * :-)
		 */
		TAILQ_REMOVE(&inp->read_queue, control, next);
		control->on_read_q = 0;
	}
}