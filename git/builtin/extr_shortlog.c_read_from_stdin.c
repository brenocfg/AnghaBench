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
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct shortlog {scalar_t__ committer; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  insert_one_record (struct shortlog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_stdin_author (struct shortlog*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void read_from_stdin(struct shortlog *log)
{
	struct strbuf author = STRBUF_INIT;
	struct strbuf mapped_author = STRBUF_INIT;
	struct strbuf oneline = STRBUF_INIT;
	static const char *author_match[2] = { "Author: ", "author " };
	static const char *committer_match[2] = { "Commit: ", "committer " };
	const char **match;

	match = log->committer ? committer_match : author_match;
	while (strbuf_getline_lf(&author, stdin) != EOF) {
		const char *v;
		if (!skip_prefix(author.buf, match[0], &v) &&
		    !skip_prefix(author.buf, match[1], &v))
			continue;
		while (strbuf_getline_lf(&oneline, stdin) != EOF &&
		       oneline.len)
			; /* discard headers */
		while (strbuf_getline_lf(&oneline, stdin) != EOF &&
		       !oneline.len)
			; /* discard blanks */

		strbuf_reset(&mapped_author);
		if (parse_stdin_author(log, &mapped_author, v) < 0)
			continue;

		insert_one_record(log, mapped_author.buf, oneline.buf);
	}
	strbuf_release(&author);
	strbuf_release(&mapped_author);
	strbuf_release(&oneline);
}