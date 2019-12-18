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
typedef  int /*<<< orphan*/  uoff_t ;
struct bio_queue_head {scalar_t__ last_offset; } ;
struct bio {scalar_t__ bio_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline uoff_t
bioq_bio_key(struct bio_queue_head *head, struct bio *bp)
{

	return ((uoff_t)(bp->bio_offset - head->last_offset));
}