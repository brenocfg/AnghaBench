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
struct file_header {int /*<<< orphan*/ * si; int /*<<< orphan*/ * fr; } ;
struct bwstring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_reader_free (int /*<<< orphan*/ *) ; 
 struct bwstring* file_reader_readline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sort_list_item_alloc () ; 
 int /*<<< orphan*/  sort_list_item_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_list_item_set (int /*<<< orphan*/ *,struct bwstring*) ; 

__attribute__((used)) static void
file_header_read_next(struct file_header *fh)
{

	if (fh && fh->fr) {
		struct bwstring *tmp;

		tmp = file_reader_readline(fh->fr);
		if (tmp == NULL) {
			file_reader_free(fh->fr);
			fh->fr = NULL;
			if (fh->si) {
				sort_list_item_clean(fh->si);
				sort_free(fh->si);
				fh->si = NULL;
			}
		} else {
			if (fh->si == NULL)
				fh->si = sort_list_item_alloc();
			sort_list_item_set(fh->si, tmp);
		}
	}
}