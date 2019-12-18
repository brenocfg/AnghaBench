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
struct val_anchors {int /*<<< orphan*/  lock; struct trust_anchor* dlv_anchor; int /*<<< orphan*/  tree; } ;
struct trust_anchor {size_t numDS; size_t numDNSKEY; int /*<<< orphan*/  lock; int /*<<< orphan*/  node; int /*<<< orphan*/  name; int /*<<< orphan*/  dclass; scalar_t__ autr; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/ * RBTREE_NULL ; 
 int /*<<< orphan*/  anchors_assemble (struct trust_anchor*) ; 
 int /*<<< orphan*/  anchors_delfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t anchors_dnskey_unsupported (struct trust_anchor*) ; 
 size_t anchors_ds_unsupported (struct trust_anchor*) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*,char*) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_first (int /*<<< orphan*/ ) ; 
 scalar_t__ rbtree_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
anchors_assemble_rrsets(struct val_anchors* anchors)
{
	struct trust_anchor* ta;
	struct trust_anchor* next;
	size_t nods, nokey;
	lock_basic_lock(&anchors->lock);
	ta=(struct trust_anchor*)rbtree_first(anchors->tree);
	while((rbnode_type*)ta != RBTREE_NULL) {
		next = (struct trust_anchor*)rbtree_next(&ta->node);
		lock_basic_lock(&ta->lock);
		if(ta->autr || (ta->numDS == 0 && ta->numDNSKEY == 0)) {
			lock_basic_unlock(&ta->lock);
			ta = next; /* skip */
			continue;
		}
		if(!anchors_assemble(ta)) {
			log_err("out of memory");
			lock_basic_unlock(&ta->lock);
			lock_basic_unlock(&anchors->lock);
			return 0;
		}
		nods = anchors_ds_unsupported(ta);
		nokey = anchors_dnskey_unsupported(ta);
		if(nods) {
			log_nametypeclass(0, "warning: unsupported "
				"algorithm for trust anchor", 
				ta->name, LDNS_RR_TYPE_DS, ta->dclass);
		}
		if(nokey) {
			log_nametypeclass(0, "warning: unsupported "
				"algorithm for trust anchor", 
				ta->name, LDNS_RR_TYPE_DNSKEY, ta->dclass);
		}
		if(nods == ta->numDS && nokey == ta->numDNSKEY) {
			char b[257];
			dname_str(ta->name, b);
			log_warn("trust anchor %s has no supported algorithms,"
				" the anchor is ignored (check if you need to"
				" upgrade unbound and "
#ifdef HAVE_LIBRESSL
				"libressl"
#else
				"openssl"
#endif
				")", b);
			(void)rbtree_delete(anchors->tree, &ta->node);
			lock_basic_unlock(&ta->lock);
			if(anchors->dlv_anchor == ta)
				anchors->dlv_anchor = NULL;
			anchors_delfunc(&ta->node, NULL);
			ta = next;
			continue;
		}
		lock_basic_unlock(&ta->lock);
		ta = next;
	}
	lock_basic_unlock(&anchors->lock);
	return 1;
}