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
struct bio_queue_head {int /*<<< orphan*/  last_offset; struct bio* insert_point; scalar_t__ batched; int /*<<< orphan*/  total; int /*<<< orphan*/  queue; } ;
struct bio {int /*<<< orphan*/  bio_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_queue ; 

void
bioq_insert_tail(struct bio_queue_head *head, struct bio *bp)
{

	TAILQ_INSERT_TAIL(&head->queue, bp, bio_queue);
	head->total++;
	head->batched = 0;
	head->insert_point = bp;
	head->last_offset = bp->bio_offset;
}