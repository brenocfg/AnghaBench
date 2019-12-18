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
struct sort_list {scalar_t__ memsize; } ;
struct file_reader {int dummy; } ;
struct file_list {int dummy; } ;
struct bwstring {int dummy; } ;

/* Variables and functions */
 scalar_t__ available_free_memory ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_list_add (struct file_list*,char*,int) ; 
 int /*<<< orphan*/  file_reader_free (struct file_reader*) ; 
 struct file_reader* file_reader_init (char const*) ; 
 struct bwstring* file_reader_readline (struct file_reader*) ; 
 char* new_tmp_file_name () ; 
 int /*<<< orphan*/  sort_list_add (struct sort_list*,struct bwstring*) ; 
 int /*<<< orphan*/  sort_list_clean (struct sort_list*) ; 
 int /*<<< orphan*/  sort_list_to_file (struct sort_list*,char*) ; 

int
procfile(const char *fsrc, struct sort_list *list, struct file_list *fl)
{
	struct file_reader *fr;

	fr = file_reader_init(fsrc);
	if (fr == NULL)
		err(2, NULL);

	/* file browse cycle */
	for (;;) {
		struct bwstring *bws;

		bws = file_reader_readline(fr);

		if (bws == NULL)
			break;

		sort_list_add(list, bws);

		if (list->memsize >= available_free_memory) {
			char *fn;

			fn = new_tmp_file_name();
			sort_list_to_file(list, fn);
			file_list_add(fl, fn, false);
			sort_list_clean(list);
		}
	}

	file_reader_free(fr);

	return (0);
}