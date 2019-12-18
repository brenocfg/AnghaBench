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
struct val_anchors {int dummy; } ;
struct trust_anchor {int /*<<< orphan*/  lock; struct ta_key* keylist; int /*<<< orphan*/  numDNSKEY; int /*<<< orphan*/  numDS; } ;
struct ta_key {struct ta_key* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 struct trust_anchor* anchor_find (struct val_anchors*,int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ anchor_find_key (struct trust_anchor*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 struct trust_anchor* anchor_new_ta (struct val_anchors*,int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ,int) ; 
 struct ta_key* anchor_new_ta_key (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 

__attribute__((used)) static struct trust_anchor*
anchor_store_new_key(struct val_anchors* anchors, uint8_t* name, uint16_t type,
	uint16_t dclass, uint8_t* rdata, size_t rdata_len)
{
	struct ta_key* k;
	struct trust_anchor* ta;
	int namelabs;
	size_t namelen;
	namelabs = dname_count_size_labels(name, &namelen);
	if(type != LDNS_RR_TYPE_DS && type != LDNS_RR_TYPE_DNSKEY) {
		log_err("Bad type for trust anchor");
		return 0;
	}
	/* lookup or create trustanchor */
	ta = anchor_find(anchors, name, namelabs, namelen, dclass);
	if(!ta) {
		ta = anchor_new_ta(anchors, name, namelabs, namelen, dclass, 1);
		if(!ta)
			return NULL;
		lock_basic_lock(&ta->lock);
	}
	if(!rdata) {
		lock_basic_unlock(&ta->lock);
		return ta;
	}
	/* look for duplicates */
	if(anchor_find_key(ta, rdata, rdata_len, type)) {
		lock_basic_unlock(&ta->lock);
		return ta;
	}
	k = anchor_new_ta_key(rdata, rdata_len, type);
	if(!k) {
		lock_basic_unlock(&ta->lock);
		return NULL;
	}
	/* add new key */
	if(type == LDNS_RR_TYPE_DS)
		ta->numDS++;
	else	ta->numDNSKEY++;
	k->next = ta->keylist;
	ta->keylist = k;
	lock_basic_unlock(&ta->lock);
	return ta;
}