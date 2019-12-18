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
struct TYPE_2__ {char* onto; char* detached_from; scalar_t__ rebase_interactive_in_progress; scalar_t__ rebase_in_progress; } ;
struct wt_status {int /*<<< orphan*/  fp; int /*<<< orphan*/  ahead_behind_flags; int /*<<< orphan*/  branch; TYPE_1__ state; int /*<<< orphan*/  oid_commit; scalar_t__ is_initial; scalar_t__ null_termination; } ;
struct branch {int dummy; } ;

/* Variables and functions */
 struct branch* branch_get (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 char* shorten_unambiguous_ref (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 int stat_tracking_info (struct branch*,int*,int*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wt_porcelain_v2_print_tracking(struct wt_status *s)
{
	struct branch *branch;
	const char *base;
	const char *branch_name;
	int ab_info, nr_ahead, nr_behind;
	char eol = s->null_termination ? '\0' : '\n';

	fprintf(s->fp, "# branch.oid %s%c",
			(s->is_initial ? "(initial)" : oid_to_hex(&s->oid_commit)),
			eol);

	if (!s->branch)
		fprintf(s->fp, "# branch.head %s%c", "(unknown)", eol);
	else {
		if (!strcmp(s->branch, "HEAD")) {
			fprintf(s->fp, "# branch.head %s%c", "(detached)", eol);

			if (s->state.rebase_in_progress ||
			    s->state.rebase_interactive_in_progress)
				branch_name = s->state.onto;
			else if (s->state.detached_from)
				branch_name = s->state.detached_from;
			else
				branch_name = "";
		} else {
			branch_name = NULL;
			skip_prefix(s->branch, "refs/heads/", &branch_name);

			fprintf(s->fp, "# branch.head %s%c", branch_name, eol);
		}

		/* Lookup stats on the upstream tracking branch, if set. */
		branch = branch_get(branch_name);
		base = NULL;
		ab_info = stat_tracking_info(branch, &nr_ahead, &nr_behind,
					     &base, 0, s->ahead_behind_flags);
		if (base) {
			base = shorten_unambiguous_ref(base, 0);
			fprintf(s->fp, "# branch.upstream %s%c", base, eol);
			free((char *)base);

			if (ab_info > 0) {
				/* different */
				if (nr_ahead || nr_behind)
					fprintf(s->fp, "# branch.ab +%d -%d%c",
						nr_ahead, nr_behind, eol);
				else
					fprintf(s->fp, "# branch.ab +? -?%c",
						eol);
			} else if (!ab_info) {
				/* same */
				fprintf(s->fp, "# branch.ab +0 -0%c", eol);
			}
		}
	}
}