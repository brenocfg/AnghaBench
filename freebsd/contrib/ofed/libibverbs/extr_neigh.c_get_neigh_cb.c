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
struct get_neigh_handler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMSG ; 
 int NL_OK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_neigh_cb_event ; 
 scalar_t__ nl_msg_parse (struct nl_msg*,int /*<<< orphan*/ *,struct get_neigh_handler*) ; 

__attribute__((used)) static int get_neigh_cb(struct nl_msg *msg, void *arg)
{
	struct get_neigh_handler *neigh_handler =
		(struct get_neigh_handler *)arg;

	if (nl_msg_parse(msg, &get_neigh_cb_event, neigh_handler) < 0)
		errno = ENOMSG;

	return NL_OK;
}