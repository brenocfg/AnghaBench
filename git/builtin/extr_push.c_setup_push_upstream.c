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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct remote {int /*<<< orphan*/  name; } ;
struct branch {int merge_nr; TYPE_1__** merge; int /*<<< orphan*/  refname; int /*<<< orphan*/  name; int /*<<< orphan*/  remote_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  die_push_simple (struct branch*,struct remote*) ; 
 char* message_detached_head_die ; 
 int /*<<< orphan*/  refspec_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_push_upstream(struct remote *remote, struct branch *branch,
				int triangular, int simple)
{
	struct strbuf refspec = STRBUF_INIT;

	if (!branch)
		die(_(message_detached_head_die), remote->name);
	if (!branch->merge_nr || !branch->merge || !branch->remote_name)
		die(_("The current branch %s has no upstream branch.\n"
		    "To push the current branch and set the remote as upstream, use\n"
		    "\n"
		    "    git push --set-upstream %s %s\n"),
		    branch->name,
		    remote->name,
		    branch->name);
	if (branch->merge_nr != 1)
		die(_("The current branch %s has multiple upstream branches, "
		    "refusing to push."), branch->name);
	if (triangular)
		die(_("You are pushing to remote '%s', which is not the upstream of\n"
		      "your current branch '%s', without telling me what to push\n"
		      "to update which remote branch."),
		    remote->name, branch->name);

	if (simple) {
		/* Additional safety */
		if (strcmp(branch->refname, branch->merge[0]->src))
			die_push_simple(branch, remote);
	}

	strbuf_addf(&refspec, "%s:%s", branch->refname, branch->merge[0]->src);
	refspec_append(&rs, refspec.buf);
}