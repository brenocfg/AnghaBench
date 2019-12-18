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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcl_list {int /*<<< orphan*/  tree; int /*<<< orphan*/  region; } ;
struct tcl_addr {int /*<<< orphan*/  node; int /*<<< orphan*/  limit; int /*<<< orphan*/  lock; } ;
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  addr_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_quick_init (int /*<<< orphan*/ *) ; 
 struct tcl_addr* regional_alloc_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct tcl_addr*
tcl_list_insert(struct tcl_list* tcl, struct sockaddr_storage* addr,
	socklen_t addrlen, int net, uint32_t limit,
	int complain_duplicates)
{
	struct tcl_addr* node = regional_alloc_zero(tcl->region,
		sizeof(struct tcl_addr));
	if(!node)
		return NULL;
	lock_quick_init(&node->lock);
	node->limit = limit;
	if(!addr_tree_insert(&tcl->tree, &node->node, addr, addrlen, net)) {
		if(complain_duplicates)
			verbose(VERB_QUERY, "duplicate tcl address ignored.");
	}
	return node;
}