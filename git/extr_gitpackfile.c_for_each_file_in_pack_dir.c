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
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  (* each_file_in_pack_dir_fn ) (int /*<<< orphan*/ ,size_t,char*,void*) ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error_errno (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dot_or_dotdot (char*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 

void for_each_file_in_pack_dir(const char *objdir,
			       each_file_in_pack_dir_fn fn,
			       void *data)
{
	struct strbuf path = STRBUF_INIT;
	size_t dirnamelen;
	DIR *dir;
	struct dirent *de;

	strbuf_addstr(&path, objdir);
	strbuf_addstr(&path, "/pack");
	dir = opendir(path.buf);
	if (!dir) {
		if (errno != ENOENT)
			error_errno("unable to open object pack directory: %s",
				    path.buf);
		strbuf_release(&path);
		return;
	}
	strbuf_addch(&path, '/');
	dirnamelen = path.len;
	while ((de = readdir(dir)) != NULL) {
		if (is_dot_or_dotdot(de->d_name))
			continue;

		strbuf_setlen(&path, dirnamelen);
		strbuf_addstr(&path, de->d_name);

		fn(path.buf, path.len, de->d_name, data);
	}

	closedir(dir);
	strbuf_release(&path);
}