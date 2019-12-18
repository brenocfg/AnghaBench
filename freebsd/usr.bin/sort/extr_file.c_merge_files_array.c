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
struct file_header {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  closefile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_header_close (struct file_header**) ; 
 int /*<<< orphan*/  file_header_init (struct file_header**,char const*,size_t) ; 
 int /*<<< orphan*/  file_headers_merge (size_t,struct file_header**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * openfile (char const*,char*) ; 
 int /*<<< orphan*/  sort_free (struct file_header**) ; 
 struct file_header** sort_malloc (size_t) ; 

__attribute__((used)) static void
merge_files_array(size_t argc, const char **argv, const char *fn_out)
{

	if (argv && fn_out) {
		struct file_header **fh;
		FILE *f_out;
		size_t i;

		f_out = openfile(fn_out, "w");

		if (f_out == NULL)
			err(2, NULL);

		fh = sort_malloc((argc + 1) * sizeof(struct file_header *));

		for (i = 0; i < argc; i++)
			file_header_init(fh + i, argv[i], (size_t) i);

		file_headers_merge(argc, fh, f_out);

		for (i = 0; i < argc; i++)
			file_header_close(fh + i);

		sort_free(fh);

		closefile(f_out, fn_out);
	}
}