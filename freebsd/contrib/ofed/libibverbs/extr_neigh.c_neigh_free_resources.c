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
struct get_neigh_handler {int /*<<< orphan*/ * sock; int /*<<< orphan*/ * link_cache; int /*<<< orphan*/ * route_cache; int /*<<< orphan*/ * neigh_cache; int /*<<< orphan*/ * found_ll_addr; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; int /*<<< orphan*/ * filter_neigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  nl_addr_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_cache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_cache_mngt_unprovide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_socket_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_neigh_put (int /*<<< orphan*/ *) ; 

void neigh_free_resources(struct get_neigh_handler *neigh_handler)
{
	/* Should be released first because it's holding a reference to dst */
	if (neigh_handler->filter_neigh != NULL) {
		rtnl_neigh_put(neigh_handler->filter_neigh);
		neigh_handler->filter_neigh = NULL;
	}

	if (neigh_handler->src != NULL) {
		nl_addr_put(neigh_handler->src);
		neigh_handler->src = NULL;
	}

	if (neigh_handler->dst != NULL) {
		nl_addr_put(neigh_handler->dst);
		neigh_handler->dst = NULL;
	}

	if (neigh_handler->found_ll_addr != NULL) {
		nl_addr_put(neigh_handler->found_ll_addr);
		neigh_handler->found_ll_addr = NULL;
	}

	if (neigh_handler->neigh_cache != NULL) {
		nl_cache_mngt_unprovide(neigh_handler->neigh_cache);
		nl_cache_free(neigh_handler->neigh_cache);
		neigh_handler->neigh_cache = NULL;
	}

	if (neigh_handler->route_cache != NULL) {
		nl_cache_mngt_unprovide(neigh_handler->route_cache);
		nl_cache_free(neigh_handler->route_cache);
		neigh_handler->route_cache = NULL;
	}

	if (neigh_handler->link_cache != NULL) {
		nl_cache_mngt_unprovide(neigh_handler->link_cache);
		nl_cache_free(neigh_handler->link_cache);
		neigh_handler->link_cache = NULL;
	}

	if (neigh_handler->sock != NULL) {
		nl_close(neigh_handler->sock);
		nl_socket_free(neigh_handler->sock);
		neigh_handler->sock = NULL;
	}
}