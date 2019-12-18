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
struct file_header {struct file_header* si; int /*<<< orphan*/ * fr; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_reader_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_free (struct file_header*) ; 
 int /*<<< orphan*/  sort_list_item_clean (struct file_header*) ; 

__attribute__((used)) static void
file_header_close(struct file_header **fh)
{

	if (fh && *fh) {
		if ((*fh)->fr) {
			file_reader_free((*fh)->fr);
			(*fh)->fr = NULL;
		}
		if ((*fh)->si) {
			sort_list_item_clean((*fh)->si);
			sort_free((*fh)->si);
			(*fh)->si = NULL;
		}
		sort_free(*fh);
		*fh = NULL;
	}
}