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
struct file_header {size_t file_pos; int /*<<< orphan*/ * si; int /*<<< orphan*/ * fr; } ;
struct bwstring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_reader_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file_reader_init (char const*) ; 
 struct bwstring* file_reader_readline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getstr (int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/ * sort_list_item_alloc () ; 
 int /*<<< orphan*/  sort_list_item_set (int /*<<< orphan*/ *,struct bwstring*) ; 
 struct file_header* sort_malloc (int) ; 

__attribute__((used)) static void
file_header_init(struct file_header **fh, const char *fn, size_t file_pos)
{

	if (fh && fn) {
		struct bwstring *line;

		*fh = sort_malloc(sizeof(struct file_header));
		(*fh)->file_pos = file_pos;
		(*fh)->fr = file_reader_init(fn);
		if ((*fh)->fr == NULL) {
			perror(fn);
			err(2, "%s", getstr(8));
		}
		line = file_reader_readline((*fh)->fr);
		if (line == NULL) {
			file_reader_free((*fh)->fr);
			(*fh)->fr = NULL;
			(*fh)->si = NULL;
		} else {
			(*fh)->si = sort_list_item_alloc();
			sort_list_item_set((*fh)->si, line);
		}
	}
}