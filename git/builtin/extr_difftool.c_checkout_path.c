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
struct checkout {int dummy; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int checkout_entry (struct cache_entry*,struct checkout const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 struct cache_entry* make_transient_cache_entry (unsigned int,struct object_id*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_path(unsigned mode, struct object_id *oid,
			 const char *path, const struct checkout *state)
{
	struct cache_entry *ce;
	int ret;

	ce = make_transient_cache_entry(mode, oid, path, 0);
	ret = checkout_entry(ce, state, NULL, NULL);

	discard_cache_entry(ce);
	return ret;
}