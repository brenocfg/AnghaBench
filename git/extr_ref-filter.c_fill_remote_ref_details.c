#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ option; int /*<<< orphan*/  push; int /*<<< orphan*/  nobracket; int /*<<< orphan*/  refname; } ;
struct TYPE_5__ {TYPE_1__ remote_ref; } ;
struct used_atom {TYPE_2__ u; } ;
struct branch {int dummy; } ;
struct TYPE_6__ {char const* gone; int /*<<< orphan*/  ahead_behind; int /*<<< orphan*/  ahead; int /*<<< orphan*/  behind; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHEAD_BEHIND_FULL ; 
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ RR_REF ; 
 scalar_t__ RR_REMOTE_NAME ; 
 scalar_t__ RR_REMOTE_REF ; 
 scalar_t__ RR_TRACK ; 
 scalar_t__ RR_TRACKSHORT ; 
 int /*<<< orphan*/  free (void*) ; 
 TYPE_3__ msgs ; 
 char* pushremote_for_branch (struct branch*,int*) ; 
 char* remote_for_branch (struct branch*,int*) ; 
 char* remote_ref_for_branch (struct branch*,int /*<<< orphan*/ ,int*) ; 
 char* show_ref (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ stat_tracking_info (struct branch*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 
 char* xstrfmt (char*,...) ; 

__attribute__((used)) static void fill_remote_ref_details(struct used_atom *atom, const char *refname,
				    struct branch *branch, const char **s)
{
	int num_ours, num_theirs;
	if (atom->u.remote_ref.option == RR_REF)
		*s = show_ref(&atom->u.remote_ref.refname, refname);
	else if (atom->u.remote_ref.option == RR_TRACK) {
		if (stat_tracking_info(branch, &num_ours, &num_theirs,
				       NULL, atom->u.remote_ref.push,
				       AHEAD_BEHIND_FULL) < 0) {
			*s = xstrdup(msgs.gone);
		} else if (!num_ours && !num_theirs)
			*s = xstrdup("");
		else if (!num_ours)
			*s = xstrfmt(msgs.behind, num_theirs);
		else if (!num_theirs)
			*s = xstrfmt(msgs.ahead, num_ours);
		else
			*s = xstrfmt(msgs.ahead_behind,
				     num_ours, num_theirs);
		if (!atom->u.remote_ref.nobracket && *s[0]) {
			const char *to_free = *s;
			*s = xstrfmt("[%s]", *s);
			free((void *)to_free);
		}
	} else if (atom->u.remote_ref.option == RR_TRACKSHORT) {
		if (stat_tracking_info(branch, &num_ours, &num_theirs,
				       NULL, atom->u.remote_ref.push,
				       AHEAD_BEHIND_FULL) < 0) {
			*s = xstrdup("");
			return;
		}
		if (!num_ours && !num_theirs)
			*s = xstrdup("=");
		else if (!num_ours)
			*s = xstrdup("<");
		else if (!num_theirs)
			*s = xstrdup(">");
		else
			*s = xstrdup("<>");
	} else if (atom->u.remote_ref.option == RR_REMOTE_NAME) {
		int explicit;
		const char *remote = atom->u.remote_ref.push ?
			pushremote_for_branch(branch, &explicit) :
			remote_for_branch(branch, &explicit);
		*s = xstrdup(explicit ? remote : "");
	} else if (atom->u.remote_ref.option == RR_REMOTE_REF) {
		int explicit;
		const char *merge;

		merge = remote_ref_for_branch(branch, atom->u.remote_ref.push,
					      &explicit);
		*s = xstrdup(explicit ? merge : "");
	} else
		BUG("unhandled RR_* enum");
}