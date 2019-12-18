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
struct bio_queue_head {scalar_t__ batched; scalar_t__ total; int /*<<< orphan*/ * insert_point; scalar_t__ last_offset; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 

void
bioq_init(struct bio_queue_head *head)
{

	TAILQ_INIT(&head->queue);
	head->last_offset = 0;
	head->insert_point = NULL;
	head->total = 0;
	head->batched = 0;
}