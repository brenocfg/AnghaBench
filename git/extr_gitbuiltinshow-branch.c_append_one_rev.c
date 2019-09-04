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
 int MAX_REVS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  append_matching_ref ; 
 int /*<<< orphan*/  append_ref (char const*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_slashes (char const*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_oid (char const*,struct object_id*) ; 
 char const* match_ref_pattern ; 
 int /*<<< orphan*/  match_ref_slash ; 
 int ref_name_cnt ; 
 int /*<<< orphan*/  sort_ref_range (int,int) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static void append_one_rev(const char *av)
{
	struct object_id revkey;
	if (!get_oid(av, &revkey)) {
		append_ref(av, &revkey, 0);
		return;
	}
	if (strchr(av, '*') || strchr(av, '?') || strchr(av, '[')) {
		/* glob style match */
		int saved_matches = ref_name_cnt;

		match_ref_pattern = av;
		match_ref_slash = count_slashes(av);
		for_each_ref(append_matching_ref, NULL);
		if (saved_matches == ref_name_cnt &&
		    ref_name_cnt < MAX_REVS)
			error(_("no matching refs with %s"), av);
		sort_ref_range(saved_matches, ref_name_cnt);
		return;
	}
	die("bad sha1 reference %s", av);
}