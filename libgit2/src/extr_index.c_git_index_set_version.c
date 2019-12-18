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
struct TYPE_4__ {unsigned int version; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 unsigned int INDEX_VERSION_NUMBER_LB ; 
 unsigned int INDEX_VERSION_NUMBER_UB ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_index_set_version(git_index *index, unsigned int version)
{
	assert(index);

	if (version < INDEX_VERSION_NUMBER_LB ||
	    version > INDEX_VERSION_NUMBER_UB) {
		git_error_set(GIT_ERROR_INDEX, "invalid version number");
		return -1;
	}

	index->version = version;

	return 0;
}