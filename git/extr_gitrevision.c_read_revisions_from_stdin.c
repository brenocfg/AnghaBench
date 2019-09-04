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
struct rev_info {int dummy; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  REVARG_CANNOT_BE_FILENAME ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ handle_revision_arg (char*,struct rev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pathspec_from_stdin (struct strbuf*,struct argv_array*) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int warn_on_object_refname_ambiguity ; 

__attribute__((used)) static void read_revisions_from_stdin(struct rev_info *revs,
				      struct argv_array *prune)
{
	struct strbuf sb;
	int seen_dashdash = 0;
	int save_warning;

	save_warning = warn_on_object_refname_ambiguity;
	warn_on_object_refname_ambiguity = 0;

	strbuf_init(&sb, 1000);
	while (strbuf_getline(&sb, stdin) != EOF) {
		int len = sb.len;
		if (!len)
			break;
		if (sb.buf[0] == '-') {
			if (len == 2 && sb.buf[1] == '-') {
				seen_dashdash = 1;
				break;
			}
			die("options not supported in --stdin mode");
		}
		if (handle_revision_arg(sb.buf, revs, 0,
					REVARG_CANNOT_BE_FILENAME))
			die("bad revision '%s'", sb.buf);
	}
	if (seen_dashdash)
		read_pathspec_from_stdin(&sb, prune);

	strbuf_release(&sb);
	warn_on_object_refname_ambiguity = save_warning;
}