#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat_data {int dummy; } ;
struct stat {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avoid_racy () ; 
 int /*<<< orphan*/  close (int) ; 
 int create_file (char*) ; 
 int /*<<< orphan*/  die_errno (char*,...) ; 
 int /*<<< orphan*/  fill_stat_data (struct stat_data*,struct stat*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ match_stat_data (struct stat_data*,struct stat*) ; 
 int /*<<< orphan*/  mkdtemp (int /*<<< orphan*/ ) ; 
 TYPE_1__ mtime_dir ; 
 int /*<<< orphan*/  remove_test_directory ; 
 scalar_t__ rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strbuf_release (TYPE_1__*) ; 
 int /*<<< orphan*/  write_or_die (int,char*,int) ; 
 char* xgetcwd () ; 
 int /*<<< orphan*/  xmkdir (char*) ; 
 int /*<<< orphan*/  xrmdir (char*) ; 
 int /*<<< orphan*/  xstat_mtime_dir (struct stat*) ; 
 int /*<<< orphan*/  xunlink (char*) ; 

__attribute__((used)) static int test_if_untracked_cache_is_supported(void)
{
	struct stat st;
	struct stat_data base;
	int fd, ret = 0;
	char *cwd;

	strbuf_addstr(&mtime_dir, "mtime-test-XXXXXX");
	if (!mkdtemp(mtime_dir.buf))
		die_errno("Could not make temporary directory");

	cwd = xgetcwd();
	fprintf(stderr, _("Testing mtime in '%s' "), cwd);
	free(cwd);

	atexit(remove_test_directory);
	xstat_mtime_dir(&st);
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
	fd = create_file("newfile");
	xstat_mtime_dir(&st);
	if (!match_stat_data(&base, &st)) {
		close(fd);
		fputc('\n', stderr);
		fprintf_ln(stderr,_("directory stat info does not "
				    "change after adding a new file"));
		goto done;
	}
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
	xmkdir("new-dir");
	xstat_mtime_dir(&st);
	if (!match_stat_data(&base, &st)) {
		close(fd);
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info does not change "
				     "after adding a new directory"));
		goto done;
	}
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
	write_or_die(fd, "data", 4);
	close(fd);
	xstat_mtime_dir(&st);
	if (match_stat_data(&base, &st)) {
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info changes "
				     "after updating a file"));
		goto done;
	}
	fputc('.', stderr);

	avoid_racy();
	close(create_file("new-dir/new"));
	xstat_mtime_dir(&st);
	if (match_stat_data(&base, &st)) {
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info changes after "
				     "adding a file inside subdirectory"));
		goto done;
	}
	fputc('.', stderr);

	avoid_racy();
	xunlink("newfile");
	xstat_mtime_dir(&st);
	if (!match_stat_data(&base, &st)) {
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info does not "
				     "change after deleting a file"));
		goto done;
	}
	fill_stat_data(&base, &st);
	fputc('.', stderr);

	avoid_racy();
	xunlink("new-dir/new");
	xrmdir("new-dir");
	xstat_mtime_dir(&st);
	if (!match_stat_data(&base, &st)) {
		fputc('\n', stderr);
		fprintf_ln(stderr, _("directory stat info does not "
				     "change after deleting a directory"));
		goto done;
	}

	if (rmdir(mtime_dir.buf))
		die_errno(_("failed to delete directory %s"), mtime_dir.buf);
	fprintf_ln(stderr, _(" OK"));
	ret = 1;

done:
	strbuf_release(&mtime_dir);
	return ret;
}