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
struct queue_stats {int /*<<< orphan*/ * parent; int /*<<< orphan*/  ifname; } ;
struct pf_altq_node {struct pf_altq_node* next; struct pf_altq_node* children; int /*<<< orphan*/  qstats; int /*<<< orphan*/  altq; } ;
struct pf_altq {int /*<<< orphan*/ * parent; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  qstats ;

/* Variables and functions */
 struct pf_altq_node* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct queue_stats const*,int) ; 
 struct pf_altq_node* pfctl_find_altq_node (struct pf_altq_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_avg (struct pf_altq_node*) ; 

void
pfctl_insert_altq_node(struct pf_altq_node **root,
    const struct pf_altq altq, const struct queue_stats qstats)
{
	struct pf_altq_node	*node;

	node = calloc(1, sizeof(struct pf_altq_node));
	if (node == NULL)
		err(1, "pfctl_insert_altq_node: calloc");
	memcpy(&node->altq, &altq, sizeof(struct pf_altq));
	memcpy(&node->qstats, &qstats, sizeof(qstats));
	node->next = node->children = NULL;

	if (*root == NULL)
		*root = node;
	else if (!altq.parent[0]) {
		struct pf_altq_node	*prev = *root;

		while (prev->next != NULL)
			prev = prev->next;
		prev->next = node;
	} else {
		struct pf_altq_node	*parent;

		parent = pfctl_find_altq_node(*root, altq.parent, altq.ifname);
		if (parent == NULL)
			errx(1, "parent %s not found", altq.parent);
		if (parent->children == NULL)
			parent->children = node;
		else {
			struct pf_altq_node *prev = parent->children;

			while (prev->next != NULL)
				prev = prev->next;
			prev->next = node;
		}
	}
	update_avg(node);
}