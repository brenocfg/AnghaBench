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
typedef  int /*<<< orphan*/  path_tracker_t ;

/* Variables and functions */
 int /*<<< orphan*/  tracker_path_add (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
tracker_path_replace(path_tracker_t *tracker,
                     const char *path)
{
  /* this will implicitly purge all previous sub-tree info from STACK.
     Thus, no need to tack the deletion explicitly. */
  tracker_path_add(tracker, path);
}