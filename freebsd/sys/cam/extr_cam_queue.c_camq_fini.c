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
struct camq {int /*<<< orphan*/ * queue_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMQ ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
camq_fini(struct camq *queue)
{
	if (queue->queue_array != NULL) {
		/*
		 * Heap algorithms like everything numbered from 1, so
		 * our pointer into the heap array is offset by one element.
		 */
		queue->queue_array++;
		free(queue->queue_array, M_CAMQ);
	}
}