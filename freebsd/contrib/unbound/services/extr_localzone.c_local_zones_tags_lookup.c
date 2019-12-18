#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct local_zones {int /*<<< orphan*/  ztree; } ;
struct TYPE_2__ {struct local_zone* key; } ;
struct local_zone {scalar_t__ dclass; size_t namelen; int namelabs; struct local_zone* parent; int /*<<< orphan*/  taglen; int /*<<< orphan*/  taglist; int /*<<< orphan*/ * name; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  rbtree_find_less_equal (int /*<<< orphan*/ *,struct local_zone*,int /*<<< orphan*/ **) ; 
 scalar_t__ taglist_intersect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

struct local_zone* 
local_zones_tags_lookup(struct local_zones* zones,
        uint8_t* name, size_t len, int labs, uint16_t dclass, uint16_t dtype,
	uint8_t* taglist, size_t taglen, int ignoretags)
{
	rbnode_type* res = NULL;
	struct local_zone *result;
	struct local_zone key;
	int m;
	/* for type DS use a zone higher when on a zonecut */
	if(dtype == LDNS_RR_TYPE_DS && !dname_is_root(name)) {
		dname_remove_label(&name, &len);
		labs--;
	}
	key.node.key = &key;
	key.dclass = dclass;
	key.name = name;
	key.namelen = len;
	key.namelabs = labs;
	rbtree_find_less_equal(&zones->ztree, &key, &res);
	result = (struct local_zone*)res;
	/* exact or smaller element (or no element) */
	if(!result || result->dclass != dclass)
		return NULL;
	/* count number of labels matched */
	(void)dname_lab_cmp(result->name, result->namelabs, key.name,
		key.namelabs, &m);
	while(result) { /* go up until qname is zone or subdomain of zone */
		if(result->namelabs <= m)
			if(ignoretags || !result->taglist ||
				taglist_intersect(result->taglist, 
				result->taglen, taglist, taglen))
				break;
		result = result->parent;
	}
	return result;
}