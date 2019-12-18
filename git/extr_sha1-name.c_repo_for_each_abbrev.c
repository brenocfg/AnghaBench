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
struct repository {int dummy; } ;
struct oid_array {int dummy; } ;
struct disambiguate_state {int always_call_fn; struct oid_array* cb_data; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  each_abbrev_fn ;

/* Variables and functions */
 struct oid_array OID_ARRAY_INIT ; 
 int /*<<< orphan*/  find_short_object_filename (struct disambiguate_state*) ; 
 int /*<<< orphan*/  find_short_packed_object (struct disambiguate_state*) ; 
 scalar_t__ init_object_disambiguation (struct repository*,char const*,int /*<<< orphan*/ ,struct disambiguate_state*) ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int oid_array_for_each_unique (struct oid_array*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  repo_collect_ambiguous ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int repo_for_each_abbrev(struct repository *r, const char *prefix,
			 each_abbrev_fn fn, void *cb_data)
{
	struct oid_array collect = OID_ARRAY_INIT;
	struct disambiguate_state ds;
	int ret;

	if (init_object_disambiguation(r, prefix, strlen(prefix), &ds) < 0)
		return -1;

	ds.always_call_fn = 1;
	ds.fn = repo_collect_ambiguous;
	ds.cb_data = &collect;
	find_short_object_filename(&ds);
	find_short_packed_object(&ds);

	ret = oid_array_for_each_unique(&collect, fn, cb_data);
	oid_array_clear(&collect);
	return ret;
}