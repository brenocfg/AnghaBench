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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct stat {scalar_t__ st_mtime; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ errno ; 
 int error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ gc_log_expire_time ; 
 char* git_pathdup (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int report_last_gc_error(void)
{
	struct strbuf sb = STRBUF_INIT;
	int ret = 0;
	ssize_t len;
	struct stat st;
	char *gc_log_path = git_pathdup("gc.log");

	if (stat(gc_log_path, &st)) {
		if (errno == ENOENT)
			goto done;

		ret = error_errno(_("cannot stat '%s'"), gc_log_path);
		goto done;
	}

	if (st.st_mtime < gc_log_expire_time)
		goto done;

	len = strbuf_read_file(&sb, gc_log_path, 0);
	if (len < 0)
		ret = error_errno(_("cannot read '%s'"), gc_log_path);
	else if (len > 0) {
		/*
		 * A previous gc failed.  Report the error, and don't
		 * bother with an automatic gc run since it is likely
		 * to fail in the same way.
		 */
		warning(_("The last gc run reported the following. "
			       "Please correct the root cause\n"
			       "and remove %s.\n"
			       "Automatic cleanup will not be performed "
			       "until the file is removed.\n\n"
			       "%s"),
			    gc_log_path, sb.buf);
		ret = 1;
	}
	strbuf_release(&sb);
done:
	free(gc_log_path);
	return ret;
}