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
typedef  int /*<<< orphan*/  u64 ;
struct rtnl_link {int dummy; } ;
struct nl_object {int dummy; } ;
struct nl_cache {int dummy; } ;

/* Variables and functions */
 void* nl_cache_find (struct nl_cache*,struct nl_object*) ; 
 struct rtnl_link* rtnl_link_macsec_alloc () ; 
 int /*<<< orphan*/  rtnl_link_macsec_set_sci (struct rtnl_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_link_put (struct rtnl_link*) ; 
 int /*<<< orphan*/  rtnl_link_set_link (struct rtnl_link*,int) ; 

__attribute__((used)) static struct rtnl_link * lookup_sc(struct nl_cache *cache, int parent, u64 sci)
{
	struct rtnl_link *needle;
	void *match;

	needle = rtnl_link_macsec_alloc();
	if (!needle)
		return NULL;

	rtnl_link_set_link(needle, parent);
	rtnl_link_macsec_set_sci(needle, sci);

	match = nl_cache_find(cache, (struct nl_object *) needle);
	rtnl_link_put(needle);

	return (struct rtnl_link *) match;
}