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
struct push_cas_option {int use_tracking_for_rest; } ;
struct push_cas {int use_tracking; int /*<<< orphan*/  expect; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct push_cas* add_cas_entry (struct push_cas_option*,char const*,int) ; 
 int /*<<< orphan*/  clear_cas_option (struct push_cas_option*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ get_oid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 char* strchrnul (char const*,char) ; 

__attribute__((used)) static int parse_push_cas_option(struct push_cas_option *cas, const char *arg, int unset)
{
	const char *colon;
	struct push_cas *entry;

	if (unset) {
		/* "--no-<option>" */
		clear_cas_option(cas);
		return 0;
	}

	if (!arg) {
		/* just "--<option>" */
		cas->use_tracking_for_rest = 1;
		return 0;
	}

	/* "--<option>=refname" or "--<option>=refname:value" */
	colon = strchrnul(arg, ':');
	entry = add_cas_entry(cas, arg, colon - arg);
	if (!*colon)
		entry->use_tracking = 1;
	else if (!colon[1])
		oidclr(&entry->expect);
	else if (get_oid(colon + 1, &entry->expect))
		return error(_("cannot parse expected object name '%s'"),
			     colon + 1);
	return 0;
}