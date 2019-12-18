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
struct blk_plug {int /*<<< orphan*/  mq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_flush_plug_list (struct blk_plug*,int) ; 
 int /*<<< orphan*/  flush_plug_callbacks (struct blk_plug*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void blk_flush_plug_list(struct blk_plug *plug, bool from_schedule)
{
	flush_plug_callbacks(plug, from_schedule);

	if (!list_empty(&plug->mq_list))
		blk_mq_flush_plug_list(plug, from_schedule);
}