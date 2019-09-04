#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wt_status {char* branch; int /*<<< orphan*/  fp; scalar_t__ null_termination; scalar_t__ no_gettext; int /*<<< orphan*/  ahead_behind_flags; scalar_t__ is_initial; } ;
struct branch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHEAD_BEHIND_QUICK ; 
 char* N_ (char*) ; 
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 int /*<<< orphan*/  WT_STATUS_LOCAL_BRANCH ; 
 int /*<<< orphan*/  WT_STATUS_NOBRANCH ; 
 int /*<<< orphan*/  WT_STATUS_REMOTE_BRANCH ; 
 char* _ (char*) ; 
 struct branch* branch_get (char const*) ; 
 char const* color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* shorten_unambiguous_ref (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int stat_tracking_info (struct branch*,int*,int*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void wt_shortstatus_print_tracking(struct wt_status *s)
{
	struct branch *branch;
	const char *header_color = color(WT_STATUS_HEADER, s);
	const char *branch_color_local = color(WT_STATUS_LOCAL_BRANCH, s);
	const char *branch_color_remote = color(WT_STATUS_REMOTE_BRANCH, s);

	const char *base;
	char *short_base;
	const char *branch_name;
	int num_ours, num_theirs, sti;
	int upstream_is_gone = 0;

	color_fprintf(s->fp, color(WT_STATUS_HEADER, s), "## ");

	if (!s->branch)
		return;
	branch_name = s->branch;

#define LABEL(string) (s->no_gettext ? (string) : _(string))

	if (s->is_initial)
		color_fprintf(s->fp, header_color, LABEL(N_("No commits yet on ")));

	if (!strcmp(s->branch, "HEAD")) {
		color_fprintf(s->fp, color(WT_STATUS_NOBRANCH, s), "%s",
			      LABEL(N_("HEAD (no branch)")));
		goto conclude;
	}

	skip_prefix(branch_name, "refs/heads/", &branch_name);

	branch = branch_get(branch_name);

	color_fprintf(s->fp, branch_color_local, "%s", branch_name);

	sti = stat_tracking_info(branch, &num_ours, &num_theirs, &base,
				 s->ahead_behind_flags);
	if (sti < 0) {
		if (!base)
			goto conclude;

		upstream_is_gone = 1;
	}

	short_base = shorten_unambiguous_ref(base, 0);
	color_fprintf(s->fp, header_color, "...");
	color_fprintf(s->fp, branch_color_remote, "%s", short_base);
	free(short_base);

	if (!upstream_is_gone && !sti)
		goto conclude;

	color_fprintf(s->fp, header_color, " [");
	if (upstream_is_gone) {
		color_fprintf(s->fp, header_color, LABEL(N_("gone")));
	} else if (s->ahead_behind_flags == AHEAD_BEHIND_QUICK) {
		color_fprintf(s->fp, header_color, LABEL(N_("different")));
	} else if (!num_ours) {
		color_fprintf(s->fp, header_color, LABEL(N_("behind ")));
		color_fprintf(s->fp, branch_color_remote, "%d", num_theirs);
	} else if (!num_theirs) {
		color_fprintf(s->fp, header_color, LABEL(N_("ahead ")));
		color_fprintf(s->fp, branch_color_local, "%d", num_ours);
	} else {
		color_fprintf(s->fp, header_color, LABEL(N_("ahead ")));
		color_fprintf(s->fp, branch_color_local, "%d", num_ours);
		color_fprintf(s->fp, header_color, ", %s", LABEL(N_("behind ")));
		color_fprintf(s->fp, branch_color_remote, "%d", num_theirs);
	}

	color_fprintf(s->fp, header_color, "]");
 conclude:
	fputc(s->null_termination ? '\0' : '\n', s->fp);
}