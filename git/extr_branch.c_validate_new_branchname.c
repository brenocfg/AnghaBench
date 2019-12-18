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
struct strbuf {scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  is_bare_repository () ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  validate_branchname (char const*,struct strbuf*) ; 

int validate_new_branchname(const char *name, struct strbuf *ref, int force)
{
	const char *head;

	if (!validate_branchname(name, ref))
		return 0;

	if (!force)
		die(_("A branch named '%s' already exists."),
		    ref->buf + strlen("refs/heads/"));

	head = resolve_ref_unsafe("HEAD", 0, NULL, NULL);
	if (!is_bare_repository() && head && !strcmp(head, ref->buf))
		die(_("Cannot force update the current branch."));

	return 1;
}