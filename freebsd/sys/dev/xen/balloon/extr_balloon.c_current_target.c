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
struct TYPE_2__ {unsigned long current_pages; unsigned long balloon_low; unsigned long balloon_high; int /*<<< orphan*/  hard_limit; int /*<<< orphan*/  target_pages; } ;

/* Variables and functions */
 TYPE_1__ bs ; 
 unsigned long min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long 
current_target(void)
{
	unsigned long target = min(bs.target_pages, bs.hard_limit);
	if (target > (bs.current_pages + bs.balloon_low + bs.balloon_high))
		target = bs.current_pages + bs.balloon_low + bs.balloon_high;
	return (target);
}