#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_ONELINE ; 
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 struct strbuf STRBUF_INIT ; 
 char* find_unique_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  parse_commit (struct commit*) ; 
 int /*<<< orphan*/  pp_commit_easy (int /*<<< orphan*/ ,struct commit*,struct strbuf*) ; 
 scalar_t__ print_sha1_ellipsis () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void describe_detached_head(const char *msg, struct commit *commit)
{
	struct strbuf sb = STRBUF_INIT;

	if (!parse_commit(commit))
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &sb);
	if (print_sha1_ellipsis()) {
		fprintf(stderr, "%s %s... %s\n", msg,
			find_unique_abbrev(&commit->object.oid, DEFAULT_ABBREV), sb.buf);
	} else {
		fprintf(stderr, "%s %s %s\n", msg,
			find_unique_abbrev(&commit->object.oid, DEFAULT_ABBREV), sb.buf);
	}
	strbuf_release(&sb);
}