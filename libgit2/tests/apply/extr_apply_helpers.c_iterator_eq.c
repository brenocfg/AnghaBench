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
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE (TYPE_1__ const*) ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iterator_eq(const git_index_entry **entry, void *_data)
{
	GIT_UNUSED(_data);

	if (!entry[0] || !entry[1])
		return -1;

	cl_assert_equal_i(GIT_INDEX_ENTRY_STAGE(entry[0]), GIT_INDEX_ENTRY_STAGE(entry[1]));
	cl_assert_equal_oid(&entry[0]->id, &entry[1]->id);
	cl_assert_equal_i(entry[0]->mode, entry[1]->mode);
	cl_assert_equal_s(entry[0]->path, entry[1]->path);

	return 0;
}