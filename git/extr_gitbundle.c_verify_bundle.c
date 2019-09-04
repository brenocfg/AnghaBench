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
struct TYPE_3__ {int nr; } ;
struct rev_info {TYPE_1__ pending; } ;
struct repository {int dummy; } ;
struct ref_list_entry {char* name; int /*<<< orphan*/  oid; } ;
struct ref_list {int nr; struct ref_list_entry* list; } ;
struct object {int flags; } ;
struct TYPE_4__ {int flags; } ;
struct commit {TYPE_2__ object; } ;
struct bundle_header {struct ref_list prerequisites; struct ref_list references; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_REV_FLAGS ; 
 int PREREQ_MARK ; 
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 int SHOWN ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,char*) ; 
 int /*<<< orphan*/  assert (struct object*) ; 
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 struct commit* get_revision (struct rev_info*) ; 
 int /*<<< orphan*/  list_refs (struct ref_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct commit* lookup_commit_reference_gently (struct repository*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 struct object* parse_object (struct repository*,int /*<<< orphan*/ *) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  printf_ln (char*,...) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_revisions (int,char const**,struct rev_info*,int /*<<< orphan*/ *) ; 

int verify_bundle(struct repository *r,
		  struct bundle_header *header,
		  int verbose)
{
	/*
	 * Do fast check, then if any prereqs are missing then go line by line
	 * to be verbose about the errors
	 */
	struct ref_list *p = &header->prerequisites;
	struct rev_info revs;
	const char *argv[] = {NULL, "--all", NULL};
	struct commit *commit;
	int i, ret = 0, req_nr;
	const char *message = _("Repository lacks these prerequisite commits:");

	repo_init_revisions(r, &revs, NULL);
	for (i = 0; i < p->nr; i++) {
		struct ref_list_entry *e = p->list + i;
		struct object *o = parse_object(r, &e->oid);
		if (o) {
			o->flags |= PREREQ_MARK;
			add_pending_object(&revs, o, e->name);
			continue;
		}
		if (++ret == 1)
			error("%s", message);
		error("%s %s", oid_to_hex(&e->oid), e->name);
	}
	if (revs.pending.nr != p->nr)
		return ret;
	req_nr = revs.pending.nr;
	setup_revisions(2, argv, &revs, NULL);

	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));

	i = req_nr;
	while (i && (commit = get_revision(&revs)))
		if (commit->object.flags & PREREQ_MARK)
			i--;

	for (i = 0; i < p->nr; i++) {
		struct ref_list_entry *e = p->list + i;
		struct object *o = parse_object(r, &e->oid);
		assert(o); /* otherwise we'd have returned early */
		if (o->flags & SHOWN)
			continue;
		if (++ret == 1)
			error("%s", message);
		error("%s %s", oid_to_hex(&e->oid), e->name);
	}

	/* Clean up objects used, as they will be reused. */
	for (i = 0; i < p->nr; i++) {
		struct ref_list_entry *e = p->list + i;
		commit = lookup_commit_reference_gently(r, &e->oid, 1);
		if (commit)
			clear_commit_marks(commit, ALL_REV_FLAGS);
	}

	if (verbose) {
		struct ref_list *r;

		r = &header->references;
		printf_ln(Q_("The bundle contains this ref:",
			     "The bundle contains these %d refs:",
			     r->nr),
			  r->nr);
		list_refs(r, 0, NULL);
		r = &header->prerequisites;
		if (!r->nr) {
			printf_ln(_("The bundle records a complete history."));
		} else {
			printf_ln(Q_("The bundle requires this ref:",
				     "The bundle requires these %d refs:",
				     r->nr),
				  r->nr);
			list_refs(r, 0, NULL);
		}
	}
	return ret;
}