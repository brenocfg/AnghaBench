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
struct cn_dev {int /*<<< orphan*/  cbdev; } ;
struct cb_id {int dummy; } ;

/* Variables and functions */
 struct cn_dev cdev ; 
 int /*<<< orphan*/  cn_queue_del_callback (int /*<<< orphan*/ ,struct cb_id*) ; 

void cn_del_callback(struct cb_id *id)
{
	struct cn_dev *dev = &cdev;

	cn_queue_del_callback(dev->cbdev, id);
}