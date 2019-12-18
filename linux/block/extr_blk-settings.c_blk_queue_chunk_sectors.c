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
struct TYPE_2__ {unsigned int chunk_sectors; } ;
struct request_queue {TYPE_1__ limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 

void blk_queue_chunk_sectors(struct request_queue *q, unsigned int chunk_sectors)
{
	BUG_ON(!is_power_of_2(chunk_sectors));
	q->limits.chunk_sectors = chunk_sectors;
}