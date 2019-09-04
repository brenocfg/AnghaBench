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
struct cache_entry {char const* name; } ;

/* Variables and functions */
 scalar_t__ CHECKOUT_ALL ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int ce_namelen (struct cache_entry*) ; 
 size_t ce_stage (struct cache_entry*) ; 
 scalar_t__ checkout_entry (struct cache_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ checkout_stage ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  state ; 
 scalar_t__ to_tempfile ; 
 int /*<<< orphan*/ ** topath ; 
 int /*<<< orphan*/  write_tempfile_record (char const*,char const*) ; 

__attribute__((used)) static void checkout_all(const char *prefix, int prefix_length)
{
	int i, errs = 0;
	struct cache_entry *last_ce = NULL;

	for (i = 0; i < active_nr ; i++) {
		struct cache_entry *ce = active_cache[i];
		if (ce_stage(ce) != checkout_stage
		    && (CHECKOUT_ALL != checkout_stage || !ce_stage(ce)))
			continue;
		if (prefix && *prefix &&
		    (ce_namelen(ce) <= prefix_length ||
		     memcmp(prefix, ce->name, prefix_length)))
			continue;
		if (last_ce && to_tempfile) {
			if (ce_namelen(last_ce) != ce_namelen(ce)
			    || memcmp(last_ce->name, ce->name, ce_namelen(ce)))
				write_tempfile_record(last_ce->name, prefix);
		}
		if (checkout_entry(ce, &state,
				   to_tempfile ? topath[ce_stage(ce)] : NULL,
				   NULL) < 0)
			errs++;
		last_ce = ce;
	}
	if (last_ce && to_tempfile)
		write_tempfile_record(last_ce->name, prefix);
	if (errs)
		/* we have already done our error reporting.
		 * exit with the same code as die().
		 */
		exit(128);
}