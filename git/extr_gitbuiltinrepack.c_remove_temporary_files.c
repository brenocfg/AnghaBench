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
struct strbuf {size_t len; scalar_t__ buf; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packdir ; 
 int /*<<< orphan*/  packtmp ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

__attribute__((used)) static void remove_temporary_files(void)
{
	struct strbuf buf = STRBUF_INIT;
	size_t dirlen, prefixlen;
	DIR *dir;
	struct dirent *e;

	dir = opendir(packdir);
	if (!dir)
		return;

	/* Point at the slash at the end of ".../objects/pack/" */
	dirlen = strlen(packdir) + 1;
	strbuf_addstr(&buf, packtmp);
	/* Hold the length of  ".tmp-%d-pack-" */
	prefixlen = buf.len - dirlen;

	while ((e = readdir(dir))) {
		if (strncmp(e->d_name, buf.buf + dirlen, prefixlen))
			continue;
		strbuf_setlen(&buf, dirlen);
		strbuf_addstr(&buf, e->d_name);
		unlink(buf.buf);
	}
	closedir(dir);
	strbuf_release(&buf);
}