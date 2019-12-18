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
struct nl_msg {int dummy; } ;
struct get_neigh_handler {scalar_t__ oif; int /*<<< orphan*/ * found_ll_addr; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMSG ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_route_cb_parser ; 
 int nl_msg_parse (struct nl_msg*,int /*<<< orphan*/ *,struct get_neigh_handler*) ; 
 int /*<<< orphan*/ * process_get_neigh_mac (struct get_neigh_handler*) ; 

__attribute__((used)) static int get_route_cb(struct nl_msg *msg, void *arg)
{
	struct get_neigh_handler *neigh_handler =
		(struct get_neigh_handler *)arg;
	int err;

	err = nl_msg_parse(msg, &get_route_cb_parser, neigh_handler);
	if (err < 0) {
		errno = ENOMSG;
		return err;
	}

	if (!neigh_handler->dst || !neigh_handler->src ||
	    neigh_handler->oif <= 0) {
		errno = EINVAL;
		return -1;
	}

	if (NULL != neigh_handler->found_ll_addr)
		goto found;

	neigh_handler->found_ll_addr =
		process_get_neigh_mac(neigh_handler);

found:
	return neigh_handler->found_ll_addr ? 0 : -1;
}