#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int timeout; } ;
struct nbd_device {TYPE_2__* disk; TYPE_1__ tag_set; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nbd_set_cmd_timeout(struct nbd_device *nbd, u64 timeout)
{
	nbd->tag_set.timeout = timeout * HZ;
	if (timeout)
		blk_queue_rq_timeout(nbd->disk->queue, timeout * HZ);
}