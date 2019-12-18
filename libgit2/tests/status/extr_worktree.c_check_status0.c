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
typedef  int /*<<< orphan*/  git_status_list ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ git_status_entry ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  entry_count0 ; 
 int /*<<< orphan*/ * entry_statuses0 ; 
 TYPE_1__* git_status_byindex (int /*<<< orphan*/ *,size_t) ; 
 size_t git_status_list_entrycount (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_status0(git_status_list *status)
{
	size_t i, max_i = git_status_list_entrycount(status);
	cl_assert_equal_sz(entry_count0, max_i);
	for (i = 0; i < max_i; ++i) {
		const git_status_entry *entry = git_status_byindex(status, i);
		cl_assert_equal_i(entry_statuses0[i], entry->status);
	}
}