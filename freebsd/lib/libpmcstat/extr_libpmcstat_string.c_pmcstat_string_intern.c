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
struct pmcstat_string {int ps_len; int ps_hash; int /*<<< orphan*/  ps_string; } ;
typedef  struct pmcstat_string const* pmcstat_interned_string ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pmcstat_string*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 struct pmcstat_string* malloc (int) ; 
 int pmcstat_string_compute_hash (char const*) ; 
 int /*<<< orphan*/ * pmcstat_string_hash ; 
 struct pmcstat_string* pmcstat_string_lookup (char const*) ; 
 int /*<<< orphan*/  ps_next ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int strlen (char const*) ; 

pmcstat_interned_string
pmcstat_string_intern(const char *s)
{
	struct pmcstat_string *ps;
	const struct pmcstat_string *cps;
	int hash, len;

	if ((cps = pmcstat_string_lookup(s)) != NULL)
		return (cps);

	hash = pmcstat_string_compute_hash(s);
	len  = strlen(s);

	if ((ps = malloc(sizeof(*ps))) == NULL)
		err(EX_OSERR, "ERROR: Could not intern string");
	ps->ps_len = len;
	ps->ps_hash = hash;
	ps->ps_string = strdup(s);
	LIST_INSERT_HEAD(&pmcstat_string_hash[hash], ps, ps_next);
	return ((pmcstat_interned_string) ps);
}