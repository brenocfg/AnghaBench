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
struct overflow_queue {size_t head; size_t size; int /*<<< orphan*/  n; int /*<<< orphan*/  name; struct netmap_slot* slots; } ;
struct netmap_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  oq_empty (struct overflow_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct netmap_slot
oq_deq(struct overflow_queue *q)
{
	struct netmap_slot s = q->slots[q->head];
	if (unlikely(oq_empty(q))) {
		D("%s: queue empty!", q->name);
		abort();
	}
	q->n--;
	q->head++;
	if (q->head >= q->size)
		q->head = 0;
	return s;
}