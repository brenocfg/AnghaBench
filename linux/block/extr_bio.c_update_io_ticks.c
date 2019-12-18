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
struct hd_struct {scalar_t__ partno; int /*<<< orphan*/  stamp; } ;
struct TYPE_2__ {struct hd_struct part0; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __part_stat_add (struct hd_struct*,int /*<<< orphan*/ ,int) ; 
 unsigned long cmpxchg (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  io_ticks ; 
 scalar_t__ likely (int) ; 
 TYPE_1__* part_to_disk (struct hd_struct*) ; 
 scalar_t__ unlikely (int) ; 

void update_io_ticks(struct hd_struct *part, unsigned long now)
{
	unsigned long stamp;
again:
	stamp = READ_ONCE(part->stamp);
	if (unlikely(stamp != now)) {
		if (likely(cmpxchg(&part->stamp, stamp, now) == stamp)) {
			__part_stat_add(part, io_ticks, 1);
		}
	}
	if (part->partno) {
		part = &part_to_disk(part)->part0;
		goto again;
	}
}