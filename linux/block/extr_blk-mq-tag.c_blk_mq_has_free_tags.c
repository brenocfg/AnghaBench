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
struct TYPE_2__ {int /*<<< orphan*/  sb; } ;
struct blk_mq_tags {TYPE_1__ bitmap_tags; } ;

/* Variables and functions */
 int sbitmap_any_bit_clear (int /*<<< orphan*/ *) ; 

bool blk_mq_has_free_tags(struct blk_mq_tags *tags)
{
	if (!tags)
		return true;

	return sbitmap_any_bit_clear(&tags->bitmap_tags.sb);
}