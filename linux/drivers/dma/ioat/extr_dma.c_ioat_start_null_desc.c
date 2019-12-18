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
struct ioatdma_chan {int /*<<< orphan*/  prep_lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAT_CHAN_DOWN ; 
 int /*<<< orphan*/  __ioat_start_null_desc (struct ioatdma_chan*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ioat_start_null_desc(struct ioatdma_chan *ioat_chan)
{
	spin_lock_bh(&ioat_chan->prep_lock);
	if (!test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		__ioat_start_null_desc(ioat_chan);
	spin_unlock_bh(&ioat_chan->prep_lock);
}