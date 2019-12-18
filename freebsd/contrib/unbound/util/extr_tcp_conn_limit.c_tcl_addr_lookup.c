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
struct tcl_list {int /*<<< orphan*/  tree; } ;
struct tcl_addr {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ addr_tree_lookup (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 

struct tcl_addr*
tcl_addr_lookup(struct tcl_list* tcl, struct sockaddr_storage* addr,
        socklen_t addrlen)
{
	return (struct tcl_addr*)addr_tree_lookup(&tcl->tree,
		addr, addrlen);
}