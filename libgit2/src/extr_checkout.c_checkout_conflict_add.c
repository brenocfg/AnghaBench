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
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ checkout_data ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_index_add (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int git_index_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_conflict_add(
	checkout_data *data,
	const git_index_entry *conflict)
{
	int error = git_index_remove(data->index, conflict->path, 0);

	if (error == GIT_ENOTFOUND)
		git_error_clear();
	else if (error < 0)
		return error;

	return git_index_add(data->index, conflict);
}