#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct progress {int dummy; } ;
struct TYPE_3__ {scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  display_progress (struct progress*,unsigned int) ; 
 int /*<<< orphan*/  object_array_pop (TYPE_1__*) ; 
 TYPE_1__ pending ; 
 scalar_t__ show_progress ; 
 struct progress* start_delayed_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_progress (struct progress**) ; 
 int traverse_one_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int traverse_reachable(void)
{
	struct progress *progress = NULL;
	unsigned int nr = 0;
	int result = 0;
	if (show_progress)
		progress = start_delayed_progress(_("Checking connectivity"), 0);
	while (pending.nr) {
		result |= traverse_one_object(object_array_pop(&pending));
		display_progress(progress, ++nr);
	}
	stop_progress(&progress);
	return !!result;
}