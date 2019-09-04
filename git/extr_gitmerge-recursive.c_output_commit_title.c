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
struct merge_remote_desc {int /*<<< orphan*/  name; } ;
struct merge_options {int call_depth; int /*<<< orphan*/  obuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  _ (char*) ; 
 int find_commit_subject (char const*,char const**) ; 
 int /*<<< orphan*/  flush_output (struct merge_options*) ; 
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 struct merge_remote_desc* merge_remote_util (struct commit*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_addchars (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  strbuf_addf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 

__attribute__((used)) static void output_commit_title(struct merge_options *o, struct commit *commit)
{
	struct merge_remote_desc *desc;

	strbuf_addchars(&o->obuf, ' ', o->call_depth * 2);
	desc = merge_remote_util(commit);
	if (desc)
		strbuf_addf(&o->obuf, "virtual %s\n", desc->name);
	else {
		strbuf_add_unique_abbrev(&o->obuf, &commit->object.oid,
					 DEFAULT_ABBREV);
		strbuf_addch(&o->obuf, ' ');
		if (parse_commit(commit) != 0)
			strbuf_addstr(&o->obuf, _("(bad commit)\n"));
		else {
			const char *title;
			const char *msg = get_commit_buffer(commit, NULL);
			int len = find_commit_subject(msg, &title);
			if (len)
				strbuf_addf(&o->obuf, "%.*s\n", len, title);
			unuse_commit_buffer(commit, msg);
		}
	}
	flush_output(o);
}