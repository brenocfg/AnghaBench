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
struct ds_queue_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  req; struct ds_info* dp; } ;
struct ds_msg_tag {int dummy; } ;
struct ds_info {int dummy; } ;
struct ds_data {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __send_ds_nack (struct ds_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_wait ; 
 int /*<<< orphan*/  ds_work_list ; 
 struct ds_queue_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ds_msg_tag*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds_data(struct ds_info *dp, struct ds_msg_tag *pkt, int len)
{
	struct ds_data *dpkt = (struct ds_data *) pkt;
	struct ds_queue_entry *qp;

	qp = kmalloc(sizeof(struct ds_queue_entry) + len, GFP_ATOMIC);
	if (!qp) {
		__send_ds_nack(dp, dpkt->handle);
	} else {
		qp->dp = dp;
		memcpy(&qp->req, pkt, len);
		list_add_tail(&qp->list, &ds_work_list);
		wake_up(&ds_wait);
	}
	return 0;
}