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
struct string_list {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void die_with_unpushed_submodules(struct string_list *needs_pushing)
{
	int i;

	fprintf(stderr, _("The following submodule paths contain changes that can\n"
			"not be found on any remote:\n"));
	for (i = 0; i < needs_pushing->nr; i++)
		fprintf(stderr, "  %s\n", needs_pushing->items[i].string);
	fprintf(stderr, _("\nPlease try\n\n"
			  "	git push --recurse-submodules=on-demand\n\n"
			  "or cd to the path and use\n\n"
			  "	git push\n\n"
			  "to push them to a remote.\n\n"));

	string_list_clear(needs_pushing, 0);

	die(_("Aborting."));
}