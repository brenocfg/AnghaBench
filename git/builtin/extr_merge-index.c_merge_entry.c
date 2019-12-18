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
struct cache_entry {int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ownbuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  oid_to_hex_r (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ one_shot ; 
 char* pgm ; 
 int /*<<< orphan*/  quiet ; 
 scalar_t__ run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int merge_entry(int pos, const char *path)
{
	int found;
	const char *arguments[] = { pgm, "", "", "", path, "", "", "", NULL };
	char hexbuf[4][GIT_MAX_HEXSZ + 1];
	char ownbuf[4][60];

	if (pos >= active_nr)
		die("git merge-index: %s not in the cache", path);
	found = 0;
	do {
		const struct cache_entry *ce = active_cache[pos];
		int stage = ce_stage(ce);

		if (strcmp(ce->name, path))
			break;
		found++;
		oid_to_hex_r(hexbuf[stage], &ce->oid);
		xsnprintf(ownbuf[stage], sizeof(ownbuf[stage]), "%o", ce->ce_mode);
		arguments[stage] = hexbuf[stage];
		arguments[stage + 4] = ownbuf[stage];
	} while (++pos < active_nr);
	if (!found)
		die("git merge-index: %s not in the cache", path);

	if (run_command_v_opt(arguments, 0)) {
		if (one_shot)
			err++;
		else {
			if (!quiet)
				die("merge program failed");
			exit(1);
		}
	}
	return found;
}