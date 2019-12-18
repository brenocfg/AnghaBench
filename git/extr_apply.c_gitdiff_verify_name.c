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
struct gitdiff_data {char* linenr; int /*<<< orphan*/  p_value; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int DIFF_NEW_NAME ; 
 int /*<<< orphan*/  TERM_TAB ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char*,...) ; 
 char* find_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_dev_null (char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int gitdiff_verify_name(struct gitdiff_data *state,
			       const char *line,
			       int isnull,
			       char **name,
			       int side)
{
	if (!*name && !isnull) {
		*name = find_name(state->root, line, NULL, state->p_value, TERM_TAB);
		return 0;
	}

	if (*name) {
		char *another;
		if (isnull)
			return error(_("git apply: bad git-diff - expected /dev/null, got %s on line %d"),
				     *name, state->linenr);
		another = find_name(state->root, line, NULL, state->p_value, TERM_TAB);
		if (!another || strcmp(another, *name)) {
			free(another);
			return error((side == DIFF_NEW_NAME) ?
			    _("git apply: bad git-diff - inconsistent new filename on line %d") :
			    _("git apply: bad git-diff - inconsistent old filename on line %d"), state->linenr);
		}
		free(another);
	} else {
		if (!is_dev_null(line))
			return error(_("git apply: bad git-diff - expected /dev/null on line %d"), state->linenr);
	}

	return 0;
}