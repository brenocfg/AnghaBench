#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct commit_name {int prio; char* path; int name_checked; TYPE_1__* tag; int /*<<< orphan*/  oid; } ;
struct TYPE_3__ {char* tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ all ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* lookup_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_tag (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void append_name(struct commit_name *n, struct strbuf *dst)
{
	if (n->prio == 2 && !n->tag) {
		n->tag = lookup_tag(the_repository, &n->oid);
		if (!n->tag || parse_tag(n->tag))
			die(_("annotated tag %s not available"), n->path);
	}
	if (n->tag && !n->name_checked) {
		if (!n->tag->tag)
			die(_("annotated tag %s has no embedded name"), n->path);
		if (strcmp(n->tag->tag, all ? n->path + 5 : n->path))
			warning(_("tag '%s' is really '%s' here"), n->tag->tag, n->path);
		n->name_checked = 1;
	}

	if (n->tag) {
		if (all)
			strbuf_addstr(dst, "tags/");
		strbuf_addstr(dst, n->tag->tag);
	} else {
		strbuf_addstr(dst, n->path);
	}
}