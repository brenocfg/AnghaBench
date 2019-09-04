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
struct strbuf {int len; char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  comment_line_char ; 
 int /*<<< orphan*/  edit_description () ; 
 int /*<<< orphan*/  git_config_set (char*,char*) ; 
 scalar_t__ launch_editor (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_branch_desc (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_commented_addf (struct strbuf*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_stripspace (struct strbuf*,int) ; 
 int /*<<< orphan*/  write_file_buf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int edit_branch_description(const char *branch_name)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf name = STRBUF_INIT;

	read_branch_desc(&buf, branch_name);
	if (!buf.len || buf.buf[buf.len-1] != '\n')
		strbuf_addch(&buf, '\n');
	strbuf_commented_addf(&buf,
		    _("Please edit the description for the branch\n"
		      "  %s\n"
		      "Lines starting with '%c' will be stripped.\n"),
		    branch_name, comment_line_char);
	write_file_buf(edit_description(), buf.buf, buf.len);
	strbuf_reset(&buf);
	if (launch_editor(edit_description(), &buf, NULL)) {
		strbuf_release(&buf);
		return -1;
	}
	strbuf_stripspace(&buf, 1);

	strbuf_addf(&name, "branch.%s.description", branch_name);
	git_config_set(name.buf, buf.len ? buf.buf : NULL);
	strbuf_release(&name);
	strbuf_release(&buf);

	return 0;
}