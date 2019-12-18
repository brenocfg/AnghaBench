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
struct rev_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int ORPHAN_CUTOFF ; 
 char* Q_ (char*,char*,int) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ advice_detached_head ; 
 int /*<<< orphan*/  describe_one_orphan (struct strbuf*,struct commit*) ; 
 char* find_unique_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct commit* get_revision (struct rev_info*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void suggest_reattach(struct commit *commit, struct rev_info *revs)
{
	struct commit *c, *last = NULL;
	struct strbuf sb = STRBUF_INIT;
	int lost = 0;
	while ((c = get_revision(revs)) != NULL) {
		if (lost < ORPHAN_CUTOFF)
			describe_one_orphan(&sb, c);
		last = c;
		lost++;
	}
	if (ORPHAN_CUTOFF < lost) {
		int more = lost - ORPHAN_CUTOFF;
		if (more == 1)
			describe_one_orphan(&sb, last);
		else
			strbuf_addf(&sb, _(" ... and %d more.\n"), more);
	}

	fprintf(stderr,
		Q_(
		/* The singular version */
		"Warning: you are leaving %d commit behind, "
		"not connected to\n"
		"any of your branches:\n\n"
		"%s\n",
		/* The plural version */
		"Warning: you are leaving %d commits behind, "
		"not connected to\n"
		"any of your branches:\n\n"
		"%s\n",
		/* Give ngettext() the count */
		lost),
		lost,
		sb.buf);
	strbuf_release(&sb);

	if (advice_detached_head)
		fprintf(stderr,
			Q_(
			/* The singular version */
			"If you want to keep it by creating a new branch, "
			"this may be a good time\nto do so with:\n\n"
			" git branch <new-branch-name> %s\n\n",
			/* The plural version */
			"If you want to keep them by creating a new branch, "
			"this may be a good time\nto do so with:\n\n"
			" git branch <new-branch-name> %s\n\n",
			/* Give ngettext() the count */
			lost),
			find_unique_abbrev(&commit->object.oid, DEFAULT_ABBREV));
}