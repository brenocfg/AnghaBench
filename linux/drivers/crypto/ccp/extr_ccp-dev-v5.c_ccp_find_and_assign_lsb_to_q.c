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
struct ccp_device {int cmd_q_count; int /*<<< orphan*/  dev; struct ccp_cmd_queue* cmd_q; } ;
struct ccp_cmd_queue {int lsb; int /*<<< orphan*/  lsbmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (unsigned long*,int) ; 
 int EINVAL ; 
 int MAX_LSB_CNT ; 
 int /*<<< orphan*/  bitmap_clear (unsigned long*,int,int) ; 
 int /*<<< orphan*/  bitmap_copy (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int find_first_bit (unsigned long*,int) ; 
 unsigned long* qlsb ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static int ccp_find_and_assign_lsb_to_q(struct ccp_device *ccp,
					int lsb_cnt, int n_lsbs,
					unsigned long *lsb_pub)
{
	DECLARE_BITMAP(qlsb, MAX_LSB_CNT);
	int bitno;
	int qlsb_wgt;
	int i;

	/* For each queue:
	 * If the count of potential LSBs available to a queue matches the
	 * ordinal given to us in lsb_cnt:
	 * Copy the mask of possible LSBs for this queue into "qlsb";
	 * For each bit in qlsb, see if the corresponding bit in the
	 * aggregation mask is set; if so, we have a match.
	 *     If we have a match, clear the bit in the aggregation to
	 *     mark it as no longer available.
	 *     If there is no match, clear the bit in qlsb and keep looking.
	 */
	for (i = 0; i < ccp->cmd_q_count; i++) {
		struct ccp_cmd_queue *cmd_q = &ccp->cmd_q[i];

		qlsb_wgt = bitmap_weight(cmd_q->lsbmask, MAX_LSB_CNT);

		if (qlsb_wgt == lsb_cnt) {
			bitmap_copy(qlsb, cmd_q->lsbmask, MAX_LSB_CNT);

			bitno = find_first_bit(qlsb, MAX_LSB_CNT);
			while (bitno < MAX_LSB_CNT) {
				if (test_bit(bitno, lsb_pub)) {
					/* We found an available LSB
					 * that this queue can access
					 */
					cmd_q->lsb = bitno;
					bitmap_clear(lsb_pub, bitno, 1);
					dev_dbg(ccp->dev,
						 "Queue %d gets LSB %d\n",
						 i, bitno);
					break;
				}
				bitmap_clear(qlsb, bitno, 1);
				bitno = find_first_bit(qlsb, MAX_LSB_CNT);
			}
			if (bitno >= MAX_LSB_CNT)
				return -EINVAL;
			n_lsbs--;
		}
	}
	return n_lsbs;
}