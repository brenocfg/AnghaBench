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
struct get_neigh_handler {int /*<<< orphan*/ * found_ll_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl_addr_get_binary_addr (int /*<<< orphan*/ *) ; 
 int nl_addr_get_len (int /*<<< orphan*/ *) ; 

int neigh_get_ll(struct get_neigh_handler *neigh_handler, void *addr_buff,
		 int addr_size) {
	int neigh_len;

	if (neigh_handler->found_ll_addr == NULL)
		return -EINVAL;

	 neigh_len = nl_addr_get_len(neigh_handler->found_ll_addr);

	if (neigh_len > addr_size)
		return -EINVAL;

	memcpy(addr_buff, nl_addr_get_binary_addr(neigh_handler->found_ll_addr),
	       neigh_len);

	return neigh_len;
}