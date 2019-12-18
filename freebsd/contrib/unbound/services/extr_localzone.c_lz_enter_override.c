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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct rbtree_type {int dummy; } ;
struct local_zones {int /*<<< orphan*/  lock; } ;
struct local_zone_override {int type; } ;
struct local_zone {int /*<<< orphan*/  lock; struct rbtree_type* override_tree; int /*<<< orphan*/  region; } ;
struct addr_tree_node {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;
typedef  int /*<<< orphan*/  dname ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  UNBOUND_DNS_PORT ; 
 int /*<<< orphan*/  addr_tree_init (struct rbtree_type*) ; 
 int /*<<< orphan*/  addr_tree_insert (struct rbtree_type*,struct addr_tree_node*,struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_zone_str2type (char*,int*) ; 
 struct local_zone* local_zones_find (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  netblockstrtoaddr (char*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ regional_alloc_zero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sldns_str2wire_dname_buf (char*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
lz_enter_override(struct local_zones* zones, char* zname, char* netblock,
	char* type, uint16_t rr_class)
{
	uint8_t dname[LDNS_MAX_DOMAINLEN+1];
	size_t dname_len = sizeof(dname);
	int dname_labs;
	struct sockaddr_storage addr;
	int net;
	socklen_t addrlen;
	struct local_zone* z;
	enum localzone_type t;

	/* parse zone name */
	if(sldns_str2wire_dname_buf(zname, dname, &dname_len) != 0) {
		log_err("cannot parse zone name in local-zone-override: %s %s",
			zname, netblock);
		return 0;
	}
	dname_labs = dname_count_labels(dname);

	/* parse netblock */
	if(!netblockstrtoaddr(netblock, UNBOUND_DNS_PORT, &addr, &addrlen,
		&net)) {
		log_err("cannot parse netblock in local-zone-override: %s %s",
			zname, netblock);
		return 0;
	}

	/* parse zone type */
	if(!local_zone_str2type(type, &t)) {
		log_err("cannot parse type in local-zone-override: %s %s %s",
			zname, netblock, type);
		return 0;
	}

	/* find localzone entry */
	lock_rw_rdlock(&zones->lock);
	z = local_zones_find(zones, dname, dname_len, dname_labs, rr_class);
	if(!z) {
		lock_rw_unlock(&zones->lock);
		log_err("no local-zone for local-zone-override %s", zname);
		return 0;
	}
	lock_rw_wrlock(&z->lock);
	lock_rw_unlock(&zones->lock);

	/* create netblock addr_tree if not present yet */
	if(!z->override_tree) {
		z->override_tree = (struct rbtree_type*)regional_alloc_zero(
			z->region, sizeof(*z->override_tree));
		if(!z->override_tree) {
			lock_rw_unlock(&z->lock);
			log_err("out of memory");
			return 0;
		}
		addr_tree_init(z->override_tree);
	}
	/* add new elem to tree */
	if(z->override_tree) {
		struct local_zone_override* n;
		n = (struct local_zone_override*)regional_alloc_zero(
			z->region, sizeof(*n));
		if(!n) {
			lock_rw_unlock(&z->lock);
			log_err("out of memory");
			return 0;
		}
		n->type = t;
		if(!addr_tree_insert(z->override_tree,
			(struct addr_tree_node*)n, &addr, addrlen, net)) {
			lock_rw_unlock(&z->lock);
			log_err("duplicate local-zone-override %s %s",
				zname, netblock);
			return 1;
		}
	}

	lock_rw_unlock(&z->lock);
	return 1;
}