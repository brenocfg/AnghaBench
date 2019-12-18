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
struct pktcdvd_device {int dummy; } ;
struct packet_data {int state; TYPE_1__* w_bio; int /*<<< orphan*/  io_wait; int /*<<< orphan*/  io_errors; int /*<<< orphan*/  sleep_time; int /*<<< orphan*/  frames; int /*<<< orphan*/  write_size; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  PACKET_FINISHED_STATE 132 
#define  PACKET_READ_WAIT_STATE 131 
#define  PACKET_RECOVERY_STATE 130 
#define  PACKET_WAITING_STATE 129 
#define  PACKET_WRITE_WAIT_STATE 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*,...) ; 
 int /*<<< orphan*/  pkt_finish_packet (struct packet_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_gather_data (struct pktcdvd_device*,struct packet_data*) ; 
 int /*<<< orphan*/  pkt_set_state (struct packet_data*,int) ; 
 int /*<<< orphan*/  pkt_start_recovery (struct packet_data*) ; 
 int /*<<< orphan*/  pkt_start_write (struct pktcdvd_device*,struct packet_data*) ; 

__attribute__((used)) static void pkt_run_state_machine(struct pktcdvd_device *pd, struct packet_data *pkt)
{
	pkt_dbg(2, pd, "pkt %d\n", pkt->id);

	for (;;) {
		switch (pkt->state) {
		case PACKET_WAITING_STATE:
			if ((pkt->write_size < pkt->frames) && (pkt->sleep_time > 0))
				return;

			pkt->sleep_time = 0;
			pkt_gather_data(pd, pkt);
			pkt_set_state(pkt, PACKET_READ_WAIT_STATE);
			break;

		case PACKET_READ_WAIT_STATE:
			if (atomic_read(&pkt->io_wait) > 0)
				return;

			if (atomic_read(&pkt->io_errors) > 0) {
				pkt_set_state(pkt, PACKET_RECOVERY_STATE);
			} else {
				pkt_start_write(pd, pkt);
			}
			break;

		case PACKET_WRITE_WAIT_STATE:
			if (atomic_read(&pkt->io_wait) > 0)
				return;

			if (!pkt->w_bio->bi_status) {
				pkt_set_state(pkt, PACKET_FINISHED_STATE);
			} else {
				pkt_set_state(pkt, PACKET_RECOVERY_STATE);
			}
			break;

		case PACKET_RECOVERY_STATE:
			if (pkt_start_recovery(pkt)) {
				pkt_start_write(pd, pkt);
			} else {
				pkt_dbg(2, pd, "No recovery possible\n");
				pkt_set_state(pkt, PACKET_FINISHED_STATE);
			}
			break;

		case PACKET_FINISHED_STATE:
			pkt_finish_packet(pkt, pkt->w_bio->bi_status);
			return;

		default:
			BUG();
			break;
		}
	}
}