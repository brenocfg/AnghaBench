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
struct ccp_device {int cmd_q_count; int /*<<< orphan*/  lsbmap; TYPE_1__* cmd_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  lsbmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int LSB_SIZE ; 
 int MAX_LSB_CNT ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int ccp_find_and_assign_lsb_to_q (struct ccp_device*,int,int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lsb_pub ; 
 int /*<<< orphan*/  qlsb ; 

__attribute__((used)) static int ccp_assign_lsbs(struct ccp_device *ccp)
{
	DECLARE_BITMAP(lsb_pub, MAX_LSB_CNT);
	DECLARE_BITMAP(qlsb, MAX_LSB_CNT);
	int n_lsbs = 0;
	int bitno;
	int i, lsb_cnt;
	int rc = 0;

	bitmap_zero(lsb_pub, MAX_LSB_CNT);

	/* Create an aggregate bitmap to get a total count of available LSBs */
	for (i = 0; i < ccp->cmd_q_count; i++)
		bitmap_or(lsb_pub,
			  lsb_pub, ccp->cmd_q[i].lsbmask,
			  MAX_LSB_CNT);

	n_lsbs = bitmap_weight(lsb_pub, MAX_LSB_CNT);

	if (n_lsbs >= ccp->cmd_q_count) {
		/* We have enough LSBS to give every queue a private LSB.
		 * Brute force search to start with the queues that are more
		 * constrained in LSB choice. When an LSB is privately
		 * assigned, it is removed from the public mask.
		 * This is an ugly N squared algorithm with some optimization.
		 */
		for (lsb_cnt = 1;
		     n_lsbs && (lsb_cnt <= MAX_LSB_CNT);
		     lsb_cnt++) {
			rc = ccp_find_and_assign_lsb_to_q(ccp, lsb_cnt, n_lsbs,
							  lsb_pub);
			if (rc < 0)
				return -EINVAL;
			n_lsbs = rc;
		}
	}

	rc = 0;
	/* What's left of the LSBs, according to the public mask, now become
	 * shared. Any zero bits in the lsb_pub mask represent an LSB region
	 * that can't be used as a shared resource, so mark the LSB slots for
	 * them as "in use".
	 */
	bitmap_copy(qlsb, lsb_pub, MAX_LSB_CNT);

	bitno = find_first_zero_bit(qlsb, MAX_LSB_CNT);
	while (bitno < MAX_LSB_CNT) {
		bitmap_set(ccp->lsbmap, bitno * LSB_SIZE, LSB_SIZE);
		bitmap_set(qlsb, bitno, 1);
		bitno = find_first_zero_bit(qlsb, MAX_LSB_CNT);
	}

	return rc;
}