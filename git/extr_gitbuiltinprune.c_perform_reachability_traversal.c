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
struct rev_info {int dummy; } ;
struct progress {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  expire ; 
 int /*<<< orphan*/  mark_reachable_objects (struct rev_info*,int,int /*<<< orphan*/ ,struct progress*) ; 
 scalar_t__ show_progress ; 
 struct progress* start_delayed_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_progress (struct progress**) ; 

__attribute__((used)) static void perform_reachability_traversal(struct rev_info *revs)
{
	static int initialized;
	struct progress *progress = NULL;

	if (initialized)
		return;

	if (show_progress)
		progress = start_delayed_progress(_("Checking connectivity"), 0);
	mark_reachable_objects(revs, 1, expire, progress);
	stop_progress(&progress);
	initialized = 1;
}