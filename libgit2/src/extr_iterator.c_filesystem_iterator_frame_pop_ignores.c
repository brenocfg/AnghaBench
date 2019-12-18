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
struct TYPE_3__ {int /*<<< orphan*/  ignores; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ filesystem_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  git_ignore__pop_dir (int /*<<< orphan*/ *) ; 
 scalar_t__ iterator__honor_ignores (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void filesystem_iterator_frame_pop_ignores(
	filesystem_iterator *iter)
{
	if (iterator__honor_ignores(&iter->base))
		git_ignore__pop_dir(&iter->ignores);
}