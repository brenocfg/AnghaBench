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
typedef  int /*<<< orphan*/  u64 ;
struct badblocks {scalar_t__ changed; int count; int /*<<< orphan*/  lock; scalar_t__ unacked_exist; int /*<<< orphan*/ * page; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BB_ACK (int /*<<< orphan*/ ) ; 
 int BB_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BB_MAKE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BB_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock_irq (int /*<<< orphan*/ *) ; 

void ack_all_badblocks(struct badblocks *bb)
{
	if (bb->page == NULL || bb->changed)
		/* no point even trying */
		return;
	write_seqlock_irq(&bb->lock);

	if (bb->changed == 0 && bb->unacked_exist) {
		u64 *p = bb->page;
		int i;

		for (i = 0; i < bb->count ; i++) {
			if (!BB_ACK(p[i])) {
				sector_t start = BB_OFFSET(p[i]);
				int len = BB_LEN(p[i]);

				p[i] = BB_MAKE(start, len, 1);
			}
		}
		bb->unacked_exist = 0;
	}
	write_sequnlock_irq(&bb->lock);
}