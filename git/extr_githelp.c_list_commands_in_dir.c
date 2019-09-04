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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
struct cmdnames {int dummy; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_cmdname (struct cmdnames*,char const*,size_t) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_executable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  strip_suffix (char const*,char*,size_t*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void list_commands_in_dir(struct cmdnames *cmds,
					 const char *path,
					 const char *prefix)
{
	DIR *dir = opendir(path);
	struct dirent *de;
	struct strbuf buf = STRBUF_INIT;
	int len;

	if (!dir)
		return;
	if (!prefix)
		prefix = "git-";

	strbuf_addf(&buf, "%s/", path);
	len = buf.len;

	while ((de = readdir(dir)) != NULL) {
		const char *ent;
		size_t entlen;

		if (!skip_prefix(de->d_name, prefix, &ent))
			continue;

		strbuf_setlen(&buf, len);
		strbuf_addstr(&buf, de->d_name);
		if (!is_executable(buf.buf))
			continue;

		entlen = strlen(ent);
		strip_suffix(ent, ".exe", &entlen);

		add_cmdname(cmds, ent, entlen);
	}
	closedir(dir);
	strbuf_release(&buf);
}