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
struct patch {scalar_t__ is_new; scalar_t__ is_delete; int /*<<< orphan*/  new_name; int /*<<< orphan*/  old_name; struct fragment* fragments; } ;
struct fragment {char const* patch; int size; struct fragment* next; scalar_t__ trailing; scalar_t__ leading; scalar_t__ newlines; scalar_t__ oldlines; int /*<<< orphan*/  linenr; } ;
struct apply_state {scalar_t__ apply_verbosity; int /*<<< orphan*/  linenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fragment*) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int parse_fragment (struct apply_state*,char const*,unsigned long,struct patch*,struct fragment*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity_silent ; 
 struct fragment* xcalloc (int,int) ; 

__attribute__((used)) static int parse_single_patch(struct apply_state *state,
			      const char *line,
			      unsigned long size,
			      struct patch *patch)
{
	unsigned long offset = 0;
	unsigned long oldlines = 0, newlines = 0, context = 0;
	struct fragment **fragp = &patch->fragments;

	while (size > 4 && !memcmp(line, "@@ -", 4)) {
		struct fragment *fragment;
		int len;

		fragment = xcalloc(1, sizeof(*fragment));
		fragment->linenr = state->linenr;
		len = parse_fragment(state, line, size, patch, fragment);
		if (len <= 0) {
			free(fragment);
			return error(_("corrupt patch at line %d"), state->linenr);
		}
		fragment->patch = line;
		fragment->size = len;
		oldlines += fragment->oldlines;
		newlines += fragment->newlines;
		context += fragment->leading + fragment->trailing;

		*fragp = fragment;
		fragp = &fragment->next;

		offset += len;
		line += len;
		size -= len;
	}

	/*
	 * If something was removed (i.e. we have old-lines) it cannot
	 * be creation, and if something was added it cannot be
	 * deletion.  However, the reverse is not true; --unified=0
	 * patches that only add are not necessarily creation even
	 * though they do not have any old lines, and ones that only
	 * delete are not necessarily deletion.
	 *
	 * Unfortunately, a real creation/deletion patch do _not_ have
	 * any context line by definition, so we cannot safely tell it
	 * apart with --unified=0 insanity.  At least if the patch has
	 * more than one hunk it is not creation or deletion.
	 */
	if (patch->is_new < 0 &&
	    (oldlines || (patch->fragments && patch->fragments->next)))
		patch->is_new = 0;
	if (patch->is_delete < 0 &&
	    (newlines || (patch->fragments && patch->fragments->next)))
		patch->is_delete = 0;

	if (0 < patch->is_new && oldlines)
		return error(_("new file %s depends on old contents"), patch->new_name);
	if (0 < patch->is_delete && newlines)
		return error(_("deleted file %s still has contents"), patch->old_name);
	if (!patch->is_delete && !newlines && context && state->apply_verbosity > verbosity_silent)
		fprintf_ln(stderr,
			   _("** warning: "
			     "file %s becomes empty but is not deleted"),
			   patch->new_name);

	return offset;
}