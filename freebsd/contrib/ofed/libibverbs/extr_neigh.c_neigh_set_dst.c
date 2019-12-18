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
struct get_neigh_handler {int /*<<< orphan*/ * dst; } ;

/* Variables and functions */
 int /*<<< orphan*/ * nl_addr_build (int,void*,size_t) ; 

int neigh_set_dst(struct get_neigh_handler *neigh_handler,
		  int family, void *buf, size_t size)
{
	neigh_handler->dst = nl_addr_build(family, buf, size);
	return neigh_handler->dst == NULL;
}