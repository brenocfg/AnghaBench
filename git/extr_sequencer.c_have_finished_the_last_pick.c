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

/* Variables and functions */
 scalar_t__ ENOENT ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error_errno (char*,char const*) ; 
 char* git_path_todo_file () ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int have_finished_the_last_pick(void)
{
	struct strbuf buf = STRBUF_INIT;
	const char *eol;
	const char *todo_path = git_path_todo_file();
	int ret = 0;

	if (strbuf_read_file(&buf, todo_path, 0) < 0) {
		if (errno == ENOENT) {
			return 0;
		} else {
			error_errno("unable to open '%s'", todo_path);
			return 0;
		}
	}
	/* If there is only one line then we are done */
	eol = strchr(buf.buf, '\n');
	if (!eol || !eol[1])
		ret = 1;

	strbuf_release(&buf);

	return ret;
}