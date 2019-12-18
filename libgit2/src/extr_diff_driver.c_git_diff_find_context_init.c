#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  line; int /*<<< orphan*/  match_line; TYPE_2__* driver; } ;
typedef  TYPE_1__ git_diff_find_context_payload ;
typedef  int /*<<< orphan*/ * git_diff_find_context_fn ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_2__ git_diff_driver ;

/* Variables and functions */
 scalar_t__ DIFF_DRIVER_PATTERNLIST ; 
 int /*<<< orphan*/ * diff_context_find ; 
 int /*<<< orphan*/  diff_context_line__pattern_match ; 
 int /*<<< orphan*/  diff_context_line__simple ; 
 int /*<<< orphan*/  git_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void git_diff_find_context_init(
	git_diff_find_context_fn *findfn_out,
	git_diff_find_context_payload *payload_out,
	git_diff_driver *driver)
{
	*findfn_out = driver ? diff_context_find : NULL;

	memset(payload_out, 0, sizeof(*payload_out));
	if (driver) {
		payload_out->driver = driver;
		payload_out->match_line = (driver->type == DIFF_DRIVER_PATTERNLIST) ?
			diff_context_line__pattern_match : diff_context_line__simple;
		git_buf_init(&payload_out->line, 0);
	}
}