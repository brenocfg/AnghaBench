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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  be ; 
 scalar_t__ be_get_bootenv_props (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ be_prop_list_alloc (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  be_prop_list_free (int /*<<< orphan*/ *) ; 
 int bectl_search_jail_paths (char*) ; 
 int jail_getid (char const*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 

__attribute__((used)) static int
bectl_locate_jail(const char *ident)
{
	nvlist_t *belist, *props;
	char *mnt;
	int jid;

	/* Try the easy-match first */
	jid = jail_getid(ident);
	/*
	 * jail_getid(0) will always return 0, because this prison does exist.
	 * bectl(8) knows that this is not what it wants, so we should fall
	 * back to mount point search.
	 */
	if (jid > 0)
		return (jid);

	/* Attempt to try it as a BE name, first */
	if (be_prop_list_alloc(&belist) != 0)
		return (-1);

	if (be_get_bootenv_props(be, belist) != 0)
		return (-1);

	if (nvlist_lookup_nvlist(belist, ident, &props) == 0) {

		/* path where a boot environment is mounted */
		if (nvlist_lookup_string(props, "mounted", &mnt) == 0) {

			/* looking for a jail that matches our bootenv path */
			jid = bectl_search_jail_paths(mnt);
			be_prop_list_free(belist);
			return (jid);
		}

		be_prop_list_free(belist);
	}

	return (-1);
}