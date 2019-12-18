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
typedef  size_t u32 ;
struct zip_device {TYPE_1__* iq; } ;
struct TYPE_2__ {int free_flag; int hw_tail; int sw_head; int /*<<< orphan*/  lock; int /*<<< orphan*/  pend_cnt; int /*<<< orphan*/  sw_tail; int /*<<< orphan*/  done_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zip_dbg (char*,...) ; 

void zip_update_cmd_bufs(struct zip_device *zip_dev, u32 queue)
{
	/* Take cmd buffer lock */
	spin_lock(&zip_dev->iq[queue].lock);

	/* Check if the previous buffer can be freed */
	if (zip_dev->iq[queue].free_flag == 1) {
		zip_dbg("Free flag. Free cmd buffer, adjust sw head and tail");
		/* Reset the free flag */
		zip_dev->iq[queue].free_flag = 0;

		/* Point the hw_tail to start of the new chunk buffer */
		zip_dev->iq[queue].hw_tail = zip_dev->iq[queue].sw_head;
	} else {
		zip_dbg("Free flag not set. increment hw tail");
		zip_dev->iq[queue].hw_tail += 16; /* 16 64_bit words = 128B */
	}

	zip_dev->iq[queue].done_cnt++;
	zip_dev->iq[queue].pend_cnt--;

	zip_dbg("sw_head :0x%lx sw_tail :0x%lx hw_tail :0x%lx",
		zip_dev->iq[queue].sw_head, zip_dev->iq[queue].sw_tail,
		zip_dev->iq[queue].hw_tail);
	zip_dbg(" Got CC : pend_cnt : %d\n", zip_dev->iq[queue].pend_cnt);

	spin_unlock(&zip_dev->iq[queue].lock);
}