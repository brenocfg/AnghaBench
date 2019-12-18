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
struct bio_queue_head {scalar_t__ batched; int /*<<< orphan*/  total; int /*<<< orphan*/  queue; int /*<<< orphan*/  last_offset; int /*<<< orphan*/ * insert_point; } ;
struct bio {int /*<<< orphan*/  bio_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_queue ; 

void
bioq_insert_head(struct bio_queue_head *head, struct bio *bp)
{

	if (head->insert_point == NULL)
		head->last_offset = bp->bio_offset;
	TAILQ_INSERT_HEAD(&head->queue, bp, bio_queue);
	head->total++;
	head->batched = 0;
}