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
struct TYPE_2__ {struct name_tree_node* key; } ;
struct name_tree_node {size_t len; struct name_tree_node* name; int /*<<< orphan*/  dclass; int /*<<< orphan*/  labs; TYPE_1__ node; } ;
typedef  struct name_tree_node uint8_t ;
struct config_strlist {int /*<<< orphan*/  str; struct config_strlist* next; } ;
struct config_file {struct config_strlist* caps_whitelist; } ;
typedef  int /*<<< orphan*/  rbtree_type ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dname_count_labels (struct name_tree_node*) ; 
 int /*<<< orphan*/  free (struct name_tree_node*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  name_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_tree_insert (int /*<<< orphan*/ *,struct name_tree_node*,struct name_tree_node*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct name_tree_node* sldns_str2wire_dname (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
caps_white_apply_cfg(rbtree_type* ntree, struct config_file* cfg)
{
	struct config_strlist* p;
	for(p=cfg->caps_whitelist; p; p=p->next) {
		struct name_tree_node* n;
		size_t len;
		uint8_t* nm = sldns_str2wire_dname(p->str, &len);
		if(!nm) {
			log_err("could not parse %s", p->str);
			return 0;
		}
		n = (struct name_tree_node*)calloc(1, sizeof(*n));
		if(!n) {
			log_err("out of memory");
			free(nm);
			return 0;
		}
		n->node.key = n;
		n->name = nm;
		n->len = len;
		n->labs = dname_count_labels(nm);
		n->dclass = LDNS_RR_CLASS_IN;
		if(!name_tree_insert(ntree, n, nm, len, n->labs, n->dclass)) {
			/* duplicate element ignored, idempotent */
			free(n->name);
			free(n);
		}
	}
	name_tree_init_parents(ntree);
	return 1;
}