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
struct strbuf {char* buf; int len; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ file_exists (char*) ; 
 int /*<<< orphan*/  is_absolute_path (char*) ; 
 int /*<<< orphan*/  strbuf_add_real_path (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

int get_common_dir_noenv(struct strbuf *sb, const char *gitdir)
{
	struct strbuf data = STRBUF_INIT;
	struct strbuf path = STRBUF_INIT;
	int ret = 0;

	strbuf_addf(&path, "%s/commondir", gitdir);
	if (file_exists(path.buf)) {
		if (strbuf_read_file(&data, path.buf, 0) <= 0)
			die_errno(_("failed to read %s"), path.buf);
		while (data.len && (data.buf[data.len - 1] == '\n' ||
				    data.buf[data.len - 1] == '\r'))
			data.len--;
		data.buf[data.len] = '\0';
		strbuf_reset(&path);
		if (!is_absolute_path(data.buf))
			strbuf_addf(&path, "%s/", gitdir);
		strbuf_addbuf(&path, &data);
		strbuf_add_real_path(sb, path.buf);
		ret = 1;
	} else {
		strbuf_addstr(sb, gitdir);
	}

	strbuf_release(&data);
	strbuf_release(&path);
	return ret;
}