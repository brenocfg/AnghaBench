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
struct index_state {int dummy; } ;
struct cache_entry {int ce_namelen; int /*<<< orphan*/  oid; scalar_t__ name; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int READ_TREE_RECURSIVE ; 
 scalar_t__ S_ISDIR (unsigned int) ; 
 int add_index_entry (struct index_state*,struct cache_entry*,int) ; 
 int /*<<< orphan*/  create_ce_flags (int) ; 
 int /*<<< orphan*/  create_ce_mode (unsigned int) ; 
 struct cache_entry* make_empty_cache_entry (struct index_state*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int read_one_entry_opt(struct index_state *istate,
			      const struct object_id *oid,
			      const char *base, int baselen,
			      const char *pathname,
			      unsigned mode, int stage, int opt)
{
	int len;
	struct cache_entry *ce;

	if (S_ISDIR(mode))
		return READ_TREE_RECURSIVE;

	len = strlen(pathname);
	ce = make_empty_cache_entry(istate, baselen + len);

	ce->ce_mode = create_ce_mode(mode);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = baselen + len;
	memcpy(ce->name, base, baselen);
	memcpy(ce->name + baselen, pathname, len+1);
	oidcpy(&ce->oid, oid);
	return add_index_entry(istate, ce, opt);
}