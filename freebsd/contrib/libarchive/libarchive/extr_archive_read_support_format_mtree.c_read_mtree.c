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
struct mtree_option {int dummy; } ;
struct mtree_entry {int dummy; } ;
struct mtree {char* archive_format_name; int /*<<< orphan*/  entries; int /*<<< orphan*/  this_entry; int /*<<< orphan*/  archive_format; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_MTREE ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  detect_form (struct archive_read*,int*) ; 
 int /*<<< orphan*/  free_options (struct mtree_option*) ; 
 int /*<<< orphan*/  isprint (char) ; 
 int process_add_entry (struct archive_read*,struct mtree*,struct mtree_option**,char*,int,struct mtree_entry**,int) ; 
 int process_global_set (struct archive_read*,struct mtree_option**,char*) ; 
 int process_global_unset (struct archive_read*,struct mtree_option**,char*) ; 
 int readline (struct archive_read*,struct mtree*,char**,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
read_mtree(struct archive_read *a, struct mtree *mtree)
{
	ssize_t len;
	uintmax_t counter;
	char *p, *s;
	struct mtree_option *global;
	struct mtree_entry *last_entry;
	int r, is_form_d;

	mtree->archive_format = ARCHIVE_FORMAT_MTREE;
	mtree->archive_format_name = "mtree";

	global = NULL;
	last_entry = NULL;

	(void)detect_form(a, &is_form_d);

	for (counter = 1; ; ++counter) {
		r = ARCHIVE_OK;
		len = readline(a, mtree, &p, 65536);
		if (len == 0) {
			mtree->this_entry = mtree->entries;
			free_options(global);
			return (ARCHIVE_OK);
		}
		if (len < 0) {
			free_options(global);
			return ((int)len);
		}
		/* Leading whitespace is never significant, ignore it. */
		while (*p == ' ' || *p == '\t') {
			++p;
			--len;
		}
		/* Skip content lines and blank lines. */
		if (*p == '#')
			continue;
		if (*p == '\r' || *p == '\n' || *p == '\0')
			continue;
		/* Non-printable characters are not allowed */
		for (s = p;s < p + len - 1; s++) {
			if (!isprint(*s)) {
				r = ARCHIVE_FATAL;
				break;
			}
		}
		if (r != ARCHIVE_OK)
			break;
		if (*p != '/') {
			r = process_add_entry(a, mtree, &global, p, len,
			    &last_entry, is_form_d);
		} else if (len > 4 && strncmp(p, "/set", 4) == 0) {
			if (p[4] != ' ' && p[4] != '\t')
				break;
			r = process_global_set(a, &global, p);
		} else if (len > 6 && strncmp(p, "/unset", 6) == 0) {
			if (p[6] != ' ' && p[6] != '\t')
				break;
			r = process_global_unset(a, &global, p);
		} else
			break;

		if (r != ARCHIVE_OK) {
			free_options(global);
			return r;
		}
	}

	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Can't parse line %ju", counter);
	free_options(global);
	return (ARCHIVE_FATAL);
}