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
struct sockaddr_storage {int dummy; } ;
struct acl_list {int /*<<< orphan*/  tree; } ;
struct acl_addr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ addr_tree_lookup (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 

struct acl_addr*
acl_addr_lookup(struct acl_list* acl, struct sockaddr_storage* addr,
        socklen_t addrlen)
{
	return (struct acl_addr*)addr_tree_lookup(&acl->tree,
		addr, addrlen);
}