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
struct string_list {int dummy; } ;
struct strbuf {scalar_t__* buf; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  abbrev_sha1_in_line (struct strbuf*) ; 
 scalar_t__ comment_line_char ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path (char*,char const*) ; 
 int /*<<< orphan*/  strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,scalar_t__*) ; 

__attribute__((used)) static int read_rebase_todolist(const char *fname, struct string_list *lines)
{
	struct strbuf line = STRBUF_INIT;
	FILE *f = fopen(git_path("%s", fname), "r");

	if (!f) {
		if (errno == ENOENT)
			return -1;
		die_errno("Could not open file %s for reading",
			  git_path("%s", fname));
	}
	while (!strbuf_getline_lf(&line, f)) {
		if (line.len && line.buf[0] == comment_line_char)
			continue;
		strbuf_trim(&line);
		if (!line.len)
			continue;
		abbrev_sha1_in_line(&line);
		string_list_append(lines, line.buf);
	}
	fclose(f);
	strbuf_release(&line);
	return 0;
}