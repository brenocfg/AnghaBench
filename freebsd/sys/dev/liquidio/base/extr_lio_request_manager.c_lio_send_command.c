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
typedef  size_t uint32_t ;
struct octeon_device {struct lio_instr_queue** instr_queue; } ;
struct lio_iq_post_status {scalar_t__ status; int /*<<< orphan*/  index; } ;
struct lio_instr_queue {int /*<<< orphan*/  post_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_INCR_INSTRQUEUE_PKT_COUNT (struct octeon_device*,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ LIO_IQ_SEND_FAILED ; 
 scalar_t__ LIO_IQ_SEND_STOP ; 
 int /*<<< orphan*/  __lio_add_to_request_list (struct lio_instr_queue*,int /*<<< orphan*/ ,void*,size_t) ; 
 struct lio_iq_post_status __lio_post_command2 (struct lio_instr_queue*,void*) ; 
 int /*<<< orphan*/  bytes_sent ; 
 int /*<<< orphan*/  instr_dropped ; 
 int /*<<< orphan*/  instr_posted ; 
 int /*<<< orphan*/  lio_ring_doorbell (struct octeon_device*,struct lio_instr_queue*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
lio_send_command(struct octeon_device *oct, uint32_t iq_no,
		 uint32_t force_db, void *cmd, void *buf,
		 uint32_t datasize, uint32_t reqtype)
{
	struct lio_iq_post_status	st;
	struct lio_instr_queue		*iq = oct->instr_queue[iq_no];

	/*
	 * Get the lock and prevent other tasks and tx interrupt handler
	 * from running.
	 */
	mtx_lock(&iq->post_lock);

	st = __lio_post_command2(iq, cmd);

	if (st.status != LIO_IQ_SEND_FAILED) {
		__lio_add_to_request_list(iq, st.index, buf, reqtype);
		LIO_INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, bytes_sent, datasize);
		LIO_INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, instr_posted, 1);

		if (force_db || (st.status == LIO_IQ_SEND_STOP))
			lio_ring_doorbell(oct, iq);
	} else {
		LIO_INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, instr_dropped, 1);
	}

	mtx_unlock(&iq->post_lock);

	/*
	 * This is only done here to expedite packets being flushed for
	 * cases where there are no IQ completion interrupts.
	 */

	return (st.status);
}