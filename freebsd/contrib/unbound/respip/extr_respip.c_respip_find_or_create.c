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
struct respip_set {int /*<<< orphan*/  ip_tree; int /*<<< orphan*/  region; } ;
struct resp_addr {int /*<<< orphan*/  node; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ addr_tree_find (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  addr_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_warn (char*,char const*) ; 
 int /*<<< orphan*/  netblockstrtoaddr (char const*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *,int*) ; 
 struct resp_addr* regional_alloc_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  respip_none ; 

__attribute__((used)) static struct resp_addr*
respip_find_or_create(struct respip_set* set, const char* ipstr, int create)
{
	struct resp_addr* node;
	struct sockaddr_storage addr;
	int net;
	socklen_t addrlen;

	if(!netblockstrtoaddr(ipstr, 0, &addr, &addrlen, &net)) {
		log_err("cannot parse netblock: '%s'", ipstr);
		return NULL;
	}
	node = (struct resp_addr*)addr_tree_find(&set->ip_tree, &addr, addrlen, net);
	if(!node && create) {
		node = regional_alloc_zero(set->region, sizeof(*node));
		if(!node) {
			log_err("out of memory");
			return NULL;
		}
		node->action = respip_none;
		if(!addr_tree_insert(&set->ip_tree, &node->node, &addr,
			addrlen, net)) {
			/* We know we didn't find it, so this should be
			 * impossible. */
			log_warn("unexpected: duplicate address: %s", ipstr);
		}
	}
	return node;
}