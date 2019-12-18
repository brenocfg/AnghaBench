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
struct expected_entry {int /*<<< orphan*/  seen; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  git_config_backend ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contains_all_cb ; 
 int /*<<< orphan*/  git_config_backend_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct expected_entry*) ; 

__attribute__((used)) static void assert_config_contains_all(git_config_backend *backend,
	struct expected_entry *entries)
{
	int i;

	cl_git_pass(git_config_backend_foreach(backend, contains_all_cb, entries));

	for (i = 0; entries[i].name; i++)
		cl_assert(entries[i].seen);
}