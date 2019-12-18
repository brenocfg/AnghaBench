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
 int /*<<< orphan*/  clear_ref_exclusion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  for_each_glob_ref_in (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  for_each_ref_in (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_excludes ; 
 int /*<<< orphan*/  show_reference ; 

__attribute__((used)) static void handle_ref_opt(const char *pattern, const char *prefix)
{
	if (pattern)
		for_each_glob_ref_in(show_reference, pattern, prefix, NULL);
	else
		for_each_ref_in(prefix, show_reference, NULL);
	clear_ref_exclusion(&ref_excludes);
}