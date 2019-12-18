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
struct prio_queue {int (* compare ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* array; int /*<<< orphan*/  cb_data; } ;
struct TYPE_2__ {int ctr; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int compare(struct prio_queue *queue, int i, int j)
{
	int cmp = queue->compare(queue->array[i].data, queue->array[j].data,
				 queue->cb_data);
	if (!cmp)
		cmp = queue->array[i].ctr - queue->array[j].ctr;
	return cmp;
}