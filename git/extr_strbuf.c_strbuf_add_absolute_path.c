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
struct strbuf {size_t len; int /*<<< orphan*/ * buf; } ;
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  is_absolute_path (char const*) ; 
 int /*<<< orphan*/  is_dir_sep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* xgetcwd () ; 

void strbuf_add_absolute_path(struct strbuf *sb, const char *path)
{
	if (!*path)
		die("The empty string is not a valid path");
	if (!is_absolute_path(path)) {
		struct stat cwd_stat, pwd_stat;
		size_t orig_len = sb->len;
		char *cwd = xgetcwd();
		char *pwd = getenv("PWD");
		if (pwd && strcmp(pwd, cwd) &&
		    !stat(cwd, &cwd_stat) &&
		    (cwd_stat.st_dev || cwd_stat.st_ino) &&
		    !stat(pwd, &pwd_stat) &&
		    pwd_stat.st_dev == cwd_stat.st_dev &&
		    pwd_stat.st_ino == cwd_stat.st_ino)
			strbuf_addstr(sb, pwd);
		else
			strbuf_addstr(sb, cwd);
		if (sb->len > orig_len && !is_dir_sep(sb->buf[sb->len - 1]))
			strbuf_addch(sb, '/');
		free(cwd);
	}
	strbuf_addstr(sb, path);
}