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
struct TYPE_2__ {scalar_t__ head; } ;
struct dn_queue {TYPE_1__ mq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dn_free_pkts (scalar_t__) ; 
 int /*<<< orphan*/  free (struct dn_queue*) ; 

int
dn_delete_queue(void *_q, void *do_free)
{
	struct dn_queue *q = _q;

	(void)do_free;
        if (q->mq.head)
                dn_free_pkts(q->mq.head);
        free(q);
        return 0;
}