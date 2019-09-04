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
struct strbuf {scalar_t__ len; char* buf; } ;
struct stat {int st_mode; } ;
struct lock_file {int dummy; } ;
struct config_store_data {void* baselen; } ;
typedef  int /*<<< orphan*/  store ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct lock_file LOCK_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ chmod (char const*,int) ; 
 scalar_t__ commit_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  config_store_data_clear (struct config_store_data*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 char const* get_lock_file_path (struct lock_file*) ; 
 char* git_pathdup (char*) ; 
 int hold_lock_file_for_update (struct lock_file*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memset (struct config_store_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  section_name_is_ok (char const*) ; 
 int section_name_match (char*,char const*) ; 
 struct strbuf store_create_section (char const*,struct config_store_data*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 void* strlen (char const*) ; 
 int warn_on_fopen_errors (char const*) ; 
 int write_error (char const*) ; 
 scalar_t__ write_in_full (int,char*,int) ; 
 scalar_t__ write_section (int,char const*,struct config_store_data*) ; 

__attribute__((used)) static int git_config_copy_or_rename_section_in_file(const char *config_filename,
				      const char *old_name,
				      const char *new_name, int copy)
{
	int ret = 0, remove = 0;
	char *filename_buf = NULL;
	struct lock_file lock = LOCK_INIT;
	int out_fd;
	char buf[1024];
	FILE *config_file = NULL;
	struct stat st;
	struct strbuf copystr = STRBUF_INIT;
	struct config_store_data store;

	memset(&store, 0, sizeof(store));

	if (new_name && !section_name_is_ok(new_name)) {
		ret = error(_("invalid section name: %s"), new_name);
		goto out_no_rollback;
	}

	if (!config_filename)
		config_filename = filename_buf = git_pathdup("config");

	out_fd = hold_lock_file_for_update(&lock, config_filename, 0);
	if (out_fd < 0) {
		ret = error(_("could not lock config file %s"), config_filename);
		goto out;
	}

	if (!(config_file = fopen(config_filename, "rb"))) {
		ret = warn_on_fopen_errors(config_filename);
		if (ret)
			goto out;
		/* no config file means nothing to rename, no error */
		goto commit_and_out;
	}

	if (fstat(fileno(config_file), &st) == -1) {
		ret = error_errno(_("fstat on %s failed"), config_filename);
		goto out;
	}

	if (chmod(get_lock_file_path(&lock), st.st_mode & 07777) < 0) {
		ret = error_errno(_("chmod on %s failed"),
				  get_lock_file_path(&lock));
		goto out;
	}

	while (fgets(buf, sizeof(buf), config_file)) {
		int i;
		int length;
		int is_section = 0;
		char *output = buf;
		for (i = 0; buf[i] && isspace(buf[i]); i++)
			; /* do nothing */
		if (buf[i] == '[') {
			/* it's a section */
			int offset;
			is_section = 1;

			/*
			 * When encountering a new section under -c we
			 * need to flush out any section we're already
			 * coping and begin anew. There might be
			 * multiple [branch "$name"] sections.
			 */
			if (copystr.len > 0) {
				if (write_in_full(out_fd, copystr.buf, copystr.len) < 0) {
					ret = write_error(get_lock_file_path(&lock));
					goto out;
				}
				strbuf_reset(&copystr);
			}

			offset = section_name_match(&buf[i], old_name);
			if (offset > 0) {
				ret++;
				if (new_name == NULL) {
					remove = 1;
					continue;
				}
				store.baselen = strlen(new_name);
				if (!copy) {
					if (write_section(out_fd, new_name, &store) < 0) {
						ret = write_error(get_lock_file_path(&lock));
						goto out;
					}
					/*
					 * We wrote out the new section, with
					 * a newline, now skip the old
					 * section's length
					 */
					output += offset + i;
					if (strlen(output) > 0) {
						/*
						 * More content means there's
						 * a declaration to put on the
						 * next line; indent with a
						 * tab
						 */
						output -= 1;
						output[0] = '\t';
					}
				} else {
					copystr = store_create_section(new_name, &store);
				}
			}
			remove = 0;
		}
		if (remove)
			continue;
		length = strlen(output);

		if (!is_section && copystr.len > 0) {
			strbuf_add(&copystr, output, length);
		}

		if (write_in_full(out_fd, output, length) < 0) {
			ret = write_error(get_lock_file_path(&lock));
			goto out;
		}
	}

	/*
	 * Copy a trailing section at the end of the config, won't be
	 * flushed by the usual "flush because we have a new section
	 * logic in the loop above.
	 */
	if (copystr.len > 0) {
		if (write_in_full(out_fd, copystr.buf, copystr.len) < 0) {
			ret = write_error(get_lock_file_path(&lock));
			goto out;
		}
		strbuf_reset(&copystr);
	}

	fclose(config_file);
	config_file = NULL;
commit_and_out:
	if (commit_lock_file(&lock) < 0)
		ret = error_errno(_("could not write config file %s"),
				  config_filename);
out:
	if (config_file)
		fclose(config_file);
	rollback_lock_file(&lock);
out_no_rollback:
	free(filename_buf);
	config_store_data_clear(&store);
	return ret;
}