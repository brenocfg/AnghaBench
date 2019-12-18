#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct pretty_print_context {scalar_t__ fmt; int /*<<< orphan*/  abbrev; } ;
struct object_id {int dummy; } ;
struct commit_list {struct commit_list* next; TYPE_2__* item; } ;
struct commit {struct commit_list* parents; } ;
struct TYPE_3__ {struct object_id oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ CMIT_FMT_ONELINE ; 
 scalar_t__ cmit_fmt_is_mail (scalar_t__) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (struct strbuf*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static void add_merge_info(const struct pretty_print_context *pp,
			   struct strbuf *sb, const struct commit *commit)
{
	struct commit_list *parent = commit->parents;

	if ((pp->fmt == CMIT_FMT_ONELINE) || (cmit_fmt_is_mail(pp->fmt)) ||
	    !parent || !parent->next)
		return;

	strbuf_addstr(sb, "Merge:");

	while (parent) {
		struct object_id *oidp = &parent->item->object.oid;
		strbuf_addch(sb, ' ');
		if (pp->abbrev)
			strbuf_add_unique_abbrev(sb, oidp, pp->abbrev);
		else
			strbuf_addstr(sb, oid_to_hex(oidp));
		parent = parent->next;
	}
	strbuf_addch(sb, '\n');
}