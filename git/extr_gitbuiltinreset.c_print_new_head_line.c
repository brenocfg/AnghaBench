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
struct strbuf {scalar_t__ len; char* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_ONELINE ; 
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 char* find_unique_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_commit_easy (int /*<<< orphan*/ ,struct commit*,struct strbuf*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void print_new_head_line(struct commit *commit)
{
	struct strbuf buf = STRBUF_INIT;

	printf(_("HEAD is now at %s"),
		find_unique_abbrev(&commit->object.oid, DEFAULT_ABBREV));

	pp_commit_easy(CMIT_FMT_ONELINE, commit, &buf);
	if (buf.len > 0)
		printf(" %s", buf.buf);
	putchar('\n');
	strbuf_release(&buf);
}