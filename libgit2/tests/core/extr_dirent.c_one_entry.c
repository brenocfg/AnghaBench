#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_4__ {int /*<<< orphan*/  names; TYPE_2__ path; } ;
typedef  TYPE_1__ walk_data ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 int GIT_ERROR ; 
 void* state_loc ; 
 int update_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int one_entry(void *state, git_buf *path)
{
	walk_data *d = (walk_data *) state;

	if (state != state_loc)
		return GIT_ERROR;

	if (path != &d->path)
		return GIT_ERROR;

	return update_count(d->names, path->ptr);
}