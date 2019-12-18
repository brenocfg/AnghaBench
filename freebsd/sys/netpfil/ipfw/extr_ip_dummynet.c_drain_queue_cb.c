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
struct TYPE_2__ {scalar_t__ length; } ;
struct dn_queue {TYPE_1__ ni; } ;

/* Variables and functions */
 int DNHT_SCAN_DEL ; 
 int /*<<< orphan*/  DN_DESTROY ; 
 int /*<<< orphan*/  dn_delete_queue (struct dn_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
drain_queue_cb(void *_q, void *arg)
{
	struct dn_queue *q = _q;

	if (q->ni.length == 0) {
		dn_delete_queue(q, DN_DESTROY);
		return DNHT_SCAN_DEL; /* queue is deleted */
	}

	return 0; /* queue isn't deleted */
}