#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_blame_options ;

/* Variables and functions */
 TYPE_1__ GIT_BLAME_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_BLAME_TRACK_COPIES_SAME_COMMIT_COPIES ; 
 int /*<<< orphan*/  GIT_UNUSED (TYPE_1__) ; 

void test_blame_harder__cc(void)
{
	git_blame_options opts = GIT_BLAME_OPTIONS_INIT;

	GIT_UNUSED(opts);

	/* Attribute the second hunk in b.txt to (E), since it was copy/pasted from
	 * a.txt in (C).
	 */
	opts.flags = GIT_BLAME_TRACK_COPIES_SAME_COMMIT_COPIES;
}