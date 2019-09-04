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
struct notes_tree {char* update_ref; char* ref; } ;

/* Variables and functions */
 int NOTES_INIT_WRITABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct notes_tree default_notes_tree ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  init_notes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 

__attribute__((used)) static struct notes_tree *init_notes_check(const char *subcommand,
					   int flags)
{
	struct notes_tree *t;
	const char *ref;
	init_notes(NULL, NULL, NULL, flags);
	t = &default_notes_tree;

	ref = (flags & NOTES_INIT_WRITABLE) ? t->update_ref : t->ref;
	if (!starts_with(ref, "refs/notes/"))
		/*
		 * TRANSLATORS: the first %s will be replaced by a git
		 * notes command: 'add', 'merge', 'remove', etc.
		 */
		die(_("refusing to %s notes in %s (outside of refs/notes/)"),
		    subcommand, ref);
	return t;
}