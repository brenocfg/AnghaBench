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
struct file_list {int /*<<< orphan*/  fns; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  merge_files_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ shrink_file_list (struct file_list*) ; 

void
merge_files(struct file_list *fl, const char *fn_out)
{

	if (fl && fn_out) {
		while (shrink_file_list(fl));

		merge_files_array(fl->count, fl->fns, fn_out);
	}
}