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
typedef  int /*<<< orphan*/  tsdn_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* opt_prof_prefix ; 
 int /*<<< orphan*/  prof_dump_filename_mtx ; 
 char const* prof_dump_prefix ; 

__attribute__((used)) static const char *
prof_dump_prefix_get(tsdn_t* tsdn) {
	malloc_mutex_assert_owner(tsdn, &prof_dump_filename_mtx);

	return prof_dump_prefix == NULL ? opt_prof_prefix : prof_dump_prefix;
}