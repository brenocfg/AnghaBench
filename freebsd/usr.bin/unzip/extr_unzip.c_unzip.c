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
typedef  int uintmax_t ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 scalar_t__ Z1_opt ; 
 int /*<<< orphan*/  ac (int) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int archive_read_open_filename (struct archive*,char const*,int) ; 
 int archive_read_support_format_zip (struct archive*) ; 
 scalar_t__ c_opt ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  errorx (char*,int) ; 
 int /*<<< orphan*/  extract (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  extract_stdout (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  list (struct archive*,struct archive_entry*) ; 
 scalar_t__ p_opt ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  q_opt ; 
 scalar_t__ t_opt ; 
 int test (struct archive*,struct archive_entry*) ; 
 int v_opt ; 
 char* y_str ; 
 scalar_t__ zipinfo_mode ; 

__attribute__((used)) static void
unzip(const char *fn)
{
	struct archive *a;
	struct archive_entry *e;
	int ret;
	uintmax_t total_size, file_count, error_count;

	if ((a = archive_read_new()) == NULL)
		error("archive_read_new failed");

	ac(archive_read_support_format_zip(a));
	ac(archive_read_open_filename(a, fn, 8192));

	if (!zipinfo_mode) {
		if (!p_opt && !q_opt)
			printf("Archive:  %s\n", fn);
		if (v_opt == 1) {
			printf("  Length     %sDate   Time    Name\n", y_str);
			printf(" --------    %s----   ----    ----\n", y_str);
		} else if (v_opt == 2) {
			printf(" Length   Method    Size  Ratio   %sDate   Time   CRC-32    Name\n", y_str);
			printf("--------  ------  ------- -----   %s----   ----   ------    ----\n", y_str);
		}
	}

	total_size = 0;
	file_count = 0;
	error_count = 0;
	for (;;) {
		ret = archive_read_next_header(a, &e);
		if (ret == ARCHIVE_EOF)
			break;
		ac(ret);
		if (!zipinfo_mode) {
			if (t_opt)
				error_count += test(a, e);
			else if (v_opt)
				list(a, e);
			else if (p_opt || c_opt)
				extract_stdout(a, e);
			else
				extract(a, e);
		} else {
			if (Z1_opt)
				list(a, e);
		}

		total_size += archive_entry_size(e);
		++file_count;
	}

	if (zipinfo_mode) {
		if (v_opt == 1) {
			printf(" --------                   %s-------\n", y_str);
			printf(" %8ju                   %s%ju file%s\n",
			    total_size, y_str, file_count, file_count != 1 ? "s" : "");
		} else if (v_opt == 2) {
			printf("--------          -------  ---                            %s-------\n", y_str);
			printf("%8ju          %7ju   0%%                            %s%ju file%s\n",
			    total_size, total_size, y_str, file_count,
			    file_count != 1 ? "s" : "");
		}
	}

	ac(archive_read_close(a));
	(void)archive_read_free(a);

	if (t_opt) {
		if (error_count > 0) {
			errorx("%ju checksum error(s) found.", error_count);
		}
		else {
			printf("No errors detected in compressed data of %s.\n",
			       fn);
		}
	}
}