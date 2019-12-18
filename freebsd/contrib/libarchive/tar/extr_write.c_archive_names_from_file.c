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
struct lafe_line_reader {int dummy; } ;
struct bsdtar {int next_line_is_dir; int flags; int return_value; int /*<<< orphan*/  names_from_file; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int OPTFLAG_NULL ; 
 int /*<<< orphan*/  do_chdir (struct bsdtar*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*) ; 
 struct lafe_line_reader* lafe_line_reader (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lafe_line_reader_free (struct lafe_line_reader*) ; 
 char* lafe_line_reader_next (struct lafe_line_reader*) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_chdir (struct bsdtar*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  write_hierarchy (struct bsdtar*,struct archive*,char const*) ; 

__attribute__((used)) static void
archive_names_from_file(struct bsdtar *bsdtar, struct archive *a)
{
	struct lafe_line_reader *lr;
	const char *line;

	bsdtar->next_line_is_dir = 0;

	lr = lafe_line_reader(bsdtar->names_from_file,
	    (bsdtar->flags & OPTFLAG_NULL));
	while ((line = lafe_line_reader_next(lr)) != NULL) {
		if (bsdtar->next_line_is_dir) {
			if (*line != '\0')
				set_chdir(bsdtar, line);
			else {
				lafe_warnc(0,
				    "Meaningless argument for -C: ''");
				bsdtar->return_value = 1;
			}
			bsdtar->next_line_is_dir = 0;
		} else if (((bsdtar->flags & OPTFLAG_NULL) == 0) &&
		    strcmp(line, "-C") == 0)
			bsdtar->next_line_is_dir = 1;
		else {
			if (*line != '/')
				do_chdir(bsdtar); /* Handle a deferred -C */
			write_hierarchy(bsdtar, a, line);
		}
	}
	lafe_line_reader_free(lr);
	if (bsdtar->next_line_is_dir)
		lafe_errc(1, errno,
		    "Unexpected end of filename list; "
		    "directory expected after -C");
}