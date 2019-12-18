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
struct get_neigh_handler {int /*<<< orphan*/  src; } ;
struct addrinfo {int /*<<< orphan*/  ai_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ENXIO ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int get_ifindex (int /*<<< orphan*/ ) ; 
 int nl_addr_info (int /*<<< orphan*/ ,struct addrinfo**) ; 

int neigh_get_oif_from_src(struct get_neigh_handler *neigh_handler)
{
	int oif = -ENODEV;
	struct addrinfo *src_info;
	int err;

	err = nl_addr_info(neigh_handler->src, &src_info);
	if (err) {
		if (!errno)
			errno = ENXIO;
		return oif;
	}

	oif = get_ifindex(src_info->ai_addr);
	if (oif <= 0)
		goto free;

free:
	freeaddrinfo(src_info);
	return oif;
}