#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nullb {TYPE_3__* q; TYPE_2__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  discard_alignment; int /*<<< orphan*/  discard_granularity; } ;
struct TYPE_7__ {TYPE_1__ limits; } ;
struct TYPE_6__ {int discard; int /*<<< orphan*/  blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (TYPE_3__*,int) ; 

__attribute__((used)) static void null_config_discard(struct nullb *nullb)
{
	if (nullb->dev->discard == false)
		return;
	nullb->q->limits.discard_granularity = nullb->dev->blocksize;
	nullb->q->limits.discard_alignment = nullb->dev->blocksize;
	blk_queue_max_discard_sectors(nullb->q, UINT_MAX >> 9);
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, nullb->q);
}