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
struct traverse_info {int pathlen; int /*<<< orphan*/  traverse_path; } ;
struct name_entry {int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct cache_entry {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFREG ; 
 int ce_namelen (struct cache_entry const*) ; 
 int df_name_compare (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int do_compare_entry_piecewise (struct cache_entry const*,struct traverse_info const*,struct name_entry const*) ; 
 int strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int tree_entry_len (struct name_entry const*) ; 

__attribute__((used)) static int do_compare_entry(const struct cache_entry *ce,
			    const struct traverse_info *info,
			    const struct name_entry *n)
{
	int len, pathlen, ce_len;
	const char *ce_name;
	int cmp;

	/*
	 * If we have not precomputed the traverse path, it is quicker
	 * to avoid doing so.  But if we have precomputed it,
	 * it is quicker to use the precomputed version.
	 */
	if (!info->traverse_path)
		return do_compare_entry_piecewise(ce, info, n);

	cmp = strncmp(ce->name, info->traverse_path, info->pathlen);
	if (cmp)
		return cmp;

	pathlen = info->pathlen;
	ce_len = ce_namelen(ce);

	if (ce_len < pathlen)
		return -1;

	ce_len -= pathlen;
	ce_name = ce->name + pathlen;

	len = tree_entry_len(n);
	return df_name_compare(ce_name, ce_len, S_IFREG, n->path, len, n->mode);
}