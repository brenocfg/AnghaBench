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
struct nl_sock {int dummy; } ;
struct nl_cache {int dummy; } ;
struct genl_family {int dummy; } ;

/* Variables and functions */
 int NLE_OBJ_NOTFOUND ; 
 int genl_ctrl_alloc_cache (struct nl_sock*,struct nl_cache**) ; 
 int genl_ctrl_grp_by_name (struct genl_family*,char const*) ; 
 struct genl_family* genl_ctrl_search_by_name (struct nl_cache*,char const*) ; 
 int /*<<< orphan*/  genl_family_put (struct genl_family*) ; 
 int /*<<< orphan*/  nl_cache_free (struct nl_cache*) ; 

int genl_ctrl_resolve_grp(struct nl_sock *sk, const char *family_name,
	const char *grp_name)
{
	struct nl_cache *cache;
	struct genl_family *family;
	int err;

	if ((err = genl_ctrl_alloc_cache(sk, &cache)) < 0)
		return err;

	family = genl_ctrl_search_by_name(cache, family_name);
	if (family == NULL) {
		err = -NLE_OBJ_NOTFOUND;
		goto errout;
	}

	err = genl_ctrl_grp_by_name(family, grp_name);
	genl_family_put(family);
errout:
	nl_cache_free(cache);

	return err;
}