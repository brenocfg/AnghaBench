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
struct rtnl_neigh {int dummy; } ;
struct get_neigh_handler {struct rtnl_neigh* filter_neigh; } ;

/* Variables and functions */

__attribute__((used)) static void set_neigh_filter(struct get_neigh_handler *neigh_handler,
			     struct rtnl_neigh *filter) {
	neigh_handler->filter_neigh = filter;
}