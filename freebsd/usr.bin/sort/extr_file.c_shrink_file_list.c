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
struct file_list {size_t count; int tmp; int /*<<< orphan*/  sz; int /*<<< orphan*/ * fns; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_add (struct file_list*,char*,int) ; 
 int /*<<< orphan*/  file_list_clean (struct file_list*) ; 
 int /*<<< orphan*/  file_list_init (struct file_list*,int) ; 
 size_t max_open_files ; 
 int /*<<< orphan*/  merge_files_array (size_t,int /*<<< orphan*/ *,char*) ; 
 char* new_tmp_file_name () ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
shrink_file_list(struct file_list *fl)
{

	if ((fl == NULL) || (size_t) (fl->count) < max_open_files)
		return (0);
	else {
		struct file_list new_fl;
		size_t indx = 0;

		file_list_init(&new_fl, true);
		while (indx < fl->count) {
			char *fnew;
			size_t num;

			num = fl->count - indx;
			fnew = new_tmp_file_name();

			if ((size_t) num >= max_open_files)
				num = max_open_files - 1;
			merge_files_array(num, fl->fns + indx, fnew);
			if (fl->tmp) {
				size_t i;

				for (i = 0; i < num; i++)
					unlink(fl->fns[indx + i]);
			}
			file_list_add(&new_fl, fnew, false);
			indx += num;
		}
		fl->tmp = false; /* already taken care of */
		file_list_clean(fl);

		fl->count = new_fl.count;
		fl->fns = new_fl.fns;
		fl->sz = new_fl.sz;
		fl->tmp = new_fl.tmp;

		return (1);
	}
}