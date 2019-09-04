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
struct prio_queue {int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void swap(struct prio_queue *queue, int i, int j)
{
	SWAP(queue->array[i], queue->array[j]);
}