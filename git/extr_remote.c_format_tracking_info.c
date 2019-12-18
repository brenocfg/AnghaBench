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
struct strbuf {int dummy; } ;
struct branch {int dummy; } ;
typedef  enum ahead_behind_flags { ____Placeholder_ahead_behind_flags } ahead_behind_flags ;

/* Variables and functions */
 int AHEAD_BEHIND_QUICK ; 
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ advice_status_hints ; 
 int /*<<< orphan*/  free (char*) ; 
 char* shorten_unambiguous_ref (char const*,int /*<<< orphan*/ ) ; 
 int stat_tracking_info (struct branch*,int*,int*,char const**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

int format_tracking_info(struct branch *branch, struct strbuf *sb,
			 enum ahead_behind_flags abf)
{
	int ours, theirs, sti;
	const char *full_base;
	char *base;
	int upstream_is_gone = 0;

	sti = stat_tracking_info(branch, &ours, &theirs, &full_base, 0, abf);
	if (sti < 0) {
		if (!full_base)
			return 0;
		upstream_is_gone = 1;
	}

	base = shorten_unambiguous_ref(full_base, 0);
	if (upstream_is_gone) {
		strbuf_addf(sb,
			_("Your branch is based on '%s', but the upstream is gone.\n"),
			base);
		if (advice_status_hints)
			strbuf_addstr(sb,
				_("  (use \"git branch --unset-upstream\" to fixup)\n"));
	} else if (!sti) {
		strbuf_addf(sb,
			_("Your branch is up to date with '%s'.\n"),
			base);
	} else if (abf == AHEAD_BEHIND_QUICK) {
		strbuf_addf(sb,
			    _("Your branch and '%s' refer to different commits.\n"),
			    base);
		if (advice_status_hints)
			strbuf_addf(sb, _("  (use \"%s\" for details)\n"),
				    "git status --ahead-behind");
	} else if (!theirs) {
		strbuf_addf(sb,
			Q_("Your branch is ahead of '%s' by %d commit.\n",
			   "Your branch is ahead of '%s' by %d commits.\n",
			   ours),
			base, ours);
		if (advice_status_hints)
			strbuf_addstr(sb,
				_("  (use \"git push\" to publish your local commits)\n"));
	} else if (!ours) {
		strbuf_addf(sb,
			Q_("Your branch is behind '%s' by %d commit, "
			       "and can be fast-forwarded.\n",
			   "Your branch is behind '%s' by %d commits, "
			       "and can be fast-forwarded.\n",
			   theirs),
			base, theirs);
		if (advice_status_hints)
			strbuf_addstr(sb,
				_("  (use \"git pull\" to update your local branch)\n"));
	} else {
		strbuf_addf(sb,
			Q_("Your branch and '%s' have diverged,\n"
			       "and have %d and %d different commit each, "
			       "respectively.\n",
			   "Your branch and '%s' have diverged,\n"
			       "and have %d and %d different commits each, "
			       "respectively.\n",
			   ours + theirs),
			base, ours, theirs);
		if (advice_status_hints)
			strbuf_addstr(sb,
				_("  (use \"git pull\" to merge the remote branch into yours)\n"));
	}
	free(base);
	return 1;
}