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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;
struct diff_options {int dummy; } ;
struct cache_entry {unsigned int ce_mode; struct object_id oid; } ;

/* Variables and functions */
 unsigned int ce_mode_from_stat (struct cache_entry const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_uptodate (struct cache_entry const*) ; 
 int check_removed (struct cache_entry const*,struct stat*) ; 
 int match_stat_with_submodule (struct diff_options*,struct cache_entry const*,struct stat*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct object_id null_oid ; 

__attribute__((used)) static int get_stat_data(const struct cache_entry *ce,
			 const struct object_id **oidp,
			 unsigned int *modep,
			 int cached, int match_missing,
			 unsigned *dirty_submodule, struct diff_options *diffopt)
{
	const struct object_id *oid = &ce->oid;
	unsigned int mode = ce->ce_mode;

	if (!cached && !ce_uptodate(ce)) {
		int changed;
		struct stat st;
		changed = check_removed(ce, &st);
		if (changed < 0)
			return -1;
		else if (changed) {
			if (match_missing) {
				*oidp = oid;
				*modep = mode;
				return 0;
			}
			return -1;
		}
		changed = match_stat_with_submodule(diffopt, ce, &st,
						    0, dirty_submodule);
		if (changed) {
			mode = ce_mode_from_stat(ce, st.st_mode);
			oid = &null_oid;
		}
	}

	*oidp = oid;
	*modep = mode;
	return 0;
}