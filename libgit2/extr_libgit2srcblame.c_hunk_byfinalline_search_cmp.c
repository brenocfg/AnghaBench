#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t lines_in_hunk; size_t final_start_line_number; } ;
typedef  TYPE_1__ git_blame_hunk ;

/* Variables and functions */

__attribute__((used)) static int hunk_byfinalline_search_cmp(const void *key, const void *entry)
{
	git_blame_hunk *hunk = (git_blame_hunk*)entry;

	size_t lineno = *(size_t*)key;
	size_t lines_in_hunk = hunk->lines_in_hunk;
	size_t final_start_line_number = hunk->final_start_line_number;

	if (lineno < final_start_line_number)
		return -1;
	if (lineno >= final_start_line_number + lines_in_hunk)
		return 1;
	return 0;
}