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
struct name_tree_node {struct name_tree_node* name; int /*<<< orphan*/  dclass; int /*<<< orphan*/  labs; int /*<<< orphan*/  len; } ;
struct dns64_env {int /*<<< orphan*/  ignore_aaaa; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dname_count_labels (struct name_tree_node*) ; 
 int /*<<< orphan*/  free (struct name_tree_node*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  name_tree_insert (int /*<<< orphan*/ *,struct name_tree_node*,struct name_tree_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct name_tree_node* sldns_str2wire_dname (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dns64_insert_ignore_aaaa(struct dns64_env* dns64_env, char* str)
{
	/* parse and insert element */
	struct name_tree_node* node;
	node = (struct name_tree_node*)calloc(1, sizeof(*node));
	if(!node) {
		log_err("out of memory");
		return 0;
	}
	node->name = sldns_str2wire_dname(str, &node->len);
	if(!node->name) {
		free(node);
		log_err("cannot parse dns64-ignore-aaaa: %s", str);
		return 0;
	}
	node->labs = dname_count_labels(node->name);
	node->dclass = LDNS_RR_CLASS_IN;
	if(!name_tree_insert(&dns64_env->ignore_aaaa, node,
		node->name, node->len, node->labs, node->dclass)) {
		/* ignore duplicate element */
		free(node->name);
		free(node);
		return 1;
	}
	return 1;
}