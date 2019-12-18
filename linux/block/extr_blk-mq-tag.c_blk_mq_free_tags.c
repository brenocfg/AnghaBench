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
struct blk_mq_tags {int /*<<< orphan*/  breserved_tags; int /*<<< orphan*/  bitmap_tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct blk_mq_tags*) ; 
 int /*<<< orphan*/  sbitmap_queue_free (int /*<<< orphan*/ *) ; 

void blk_mq_free_tags(struct blk_mq_tags *tags)
{
	sbitmap_queue_free(&tags->bitmap_tags);
	sbitmap_queue_free(&tags->breserved_tags);
	kfree(tags);
}