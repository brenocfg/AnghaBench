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
struct iter_priv {int /*<<< orphan*/  a; int /*<<< orphan*/  region; } ;
struct config_strlist {int /*<<< orphan*/  str; struct config_strlist* next; } ;
struct config_file {struct config_strlist* private_address; } ;
struct addr_tree_node {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  addr_tree_insert (int /*<<< orphan*/ *,struct addr_tree_node*,struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  netblockstrtoaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ regional_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_addrs(struct iter_priv* priv, struct config_file* cfg)
{
	/* parse addresses, report errors, insert into tree */
	struct config_strlist* p;
	struct addr_tree_node* n;
	struct sockaddr_storage addr;
	int net;
	socklen_t addrlen;

	for(p = cfg->private_address; p; p = p->next) {
		log_assert(p->str);
		if(!netblockstrtoaddr(p->str, UNBOUND_DNS_PORT, &addr, 
			&addrlen, &net)) {
			log_err("cannot parse private-address: %s", p->str);
			return 0;
		}
		n = (struct addr_tree_node*)regional_alloc(priv->region,
			sizeof(*n));
		if(!n) {
			log_err("out of memory");
			return 0;
		}
		if(!addr_tree_insert(&priv->a, n, &addr, addrlen, net)) {
			verbose(VERB_QUERY, "ignoring duplicate "
				"private-address: %s", p->str);
		}
	}
	return 1;
}