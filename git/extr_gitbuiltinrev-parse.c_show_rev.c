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
struct object_id {int dummy; } ;

/* Variables and functions */
 int DO_REVS ; 
 scalar_t__ SHOW_SYMBOLIC_FULL ; 
 scalar_t__ abbrev ; 
 scalar_t__ abbrev_ref ; 
 int /*<<< orphan*/  abbrev_ref_strict ; 
 int /*<<< orphan*/ * def ; 
 int dwim_ref (char const*,int /*<<< orphan*/ ,struct object_id*,char**) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int filter ; 
 char const* find_unique_abbrev (struct object_id const*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 char const* oid_to_hex (struct object_id const*) ; 
 char* shorten_unambiguous_ref (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_with_type (int,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ symbolic ; 

__attribute__((used)) static void show_rev(int type, const struct object_id *oid, const char *name)
{
	if (!(filter & DO_REVS))
		return;
	def = NULL;

	if ((symbolic || abbrev_ref) && name) {
		if (symbolic == SHOW_SYMBOLIC_FULL || abbrev_ref) {
			struct object_id discard;
			char *full;

			switch (dwim_ref(name, strlen(name), &discard, &full)) {
			case 0:
				/*
				 * Not found -- not a ref.  We could
				 * emit "name" here, but symbolic-full
				 * users are interested in finding the
				 * refs spelled in full, and they would
				 * need to filter non-refs if we did so.
				 */
				break;
			case 1: /* happy */
				if (abbrev_ref)
					full = shorten_unambiguous_ref(full,
						abbrev_ref_strict);
				show_with_type(type, full);
				break;
			default: /* ambiguous */
				error("refname '%s' is ambiguous", name);
				break;
			}
			free(full);
		} else {
			show_with_type(type, name);
		}
	}
	else if (abbrev)
		show_with_type(type, find_unique_abbrev(oid, abbrev));
	else
		show_with_type(type, oid_to_hex(oid));
}