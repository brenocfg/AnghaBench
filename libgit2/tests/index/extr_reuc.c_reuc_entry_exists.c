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

/* Variables and functions */
 int /*<<< orphan*/ * git_index_reuc_get_bypath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo_index ; 

__attribute__((used)) static int reuc_entry_exists(void)
{
	return (git_index_reuc_get_bypath(repo_index, "newfile.txt") != NULL);
}