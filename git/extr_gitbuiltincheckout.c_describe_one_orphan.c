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
struct strbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_ONELINE ; 
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  parse_commit (struct commit*) ; 
 int /*<<< orphan*/  pp_commit_easy (int /*<<< orphan*/ ,struct commit*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static void describe_one_orphan(struct strbuf *sb, struct commit *commit)
{
	strbuf_addstr(sb, "  ");
	strbuf_add_unique_abbrev(sb, &commit->object.oid, DEFAULT_ABBREV);
	strbuf_addch(sb, ' ');
	if (!parse_commit(commit))
		pp_commit_easy(CMIT_FMT_ONELINE, commit, sb);
	strbuf_addch(sb, '\n');
}