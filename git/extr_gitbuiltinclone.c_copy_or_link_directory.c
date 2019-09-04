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
struct strbuf {int len; scalar_t__ buf; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_alternates (struct strbuf*,struct strbuf*,char const*) ; 
 scalar_t__ copy_file_with_time (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  link (scalar_t__,scalar_t__) ; 
 scalar_t__ mkdir (scalar_t__,int) ; 
 int /*<<< orphan*/ * opendir (scalar_t__) ; 
 scalar_t__ option_local ; 
 int option_no_hardlinks ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ stat (scalar_t__,struct stat*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 scalar_t__ unlink (scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void copy_or_link_directory(struct strbuf *src, struct strbuf *dest,
				   const char *src_repo, int src_baselen)
{
	struct dirent *de;
	struct stat buf;
	int src_len, dest_len;
	DIR *dir;

	dir = opendir(src->buf);
	if (!dir)
		die_errno(_("failed to open '%s'"), src->buf);

	if (mkdir(dest->buf, 0777)) {
		if (errno != EEXIST)
			die_errno(_("failed to create directory '%s'"), dest->buf);
		else if (stat(dest->buf, &buf))
			die_errno(_("failed to stat '%s'"), dest->buf);
		else if (!S_ISDIR(buf.st_mode))
			die(_("%s exists and is not a directory"), dest->buf);
	}

	strbuf_addch(src, '/');
	src_len = src->len;
	strbuf_addch(dest, '/');
	dest_len = dest->len;

	while ((de = readdir(dir)) != NULL) {
		strbuf_setlen(src, src_len);
		strbuf_addstr(src, de->d_name);
		strbuf_setlen(dest, dest_len);
		strbuf_addstr(dest, de->d_name);
		if (stat(src->buf, &buf)) {
			warning (_("failed to stat %s\n"), src->buf);
			continue;
		}
		if (S_ISDIR(buf.st_mode)) {
			if (de->d_name[0] != '.')
				copy_or_link_directory(src, dest,
						       src_repo, src_baselen);
			continue;
		}

		/* Files that cannot be copied bit-for-bit... */
		if (!strcmp(src->buf + src_baselen, "/info/alternates")) {
			copy_alternates(src, dest, src_repo);
			continue;
		}

		if (unlink(dest->buf) && errno != ENOENT)
			die_errno(_("failed to unlink '%s'"), dest->buf);
		if (!option_no_hardlinks) {
			if (!link(src->buf, dest->buf))
				continue;
			if (option_local > 0)
				die_errno(_("failed to create link '%s'"), dest->buf);
			option_no_hardlinks = 1;
		}
		if (copy_file_with_time(dest->buf, src->buf, 0666))
			die_errno(_("failed to copy file to '%s'"), dest->buf);
	}
	closedir(dir);
}