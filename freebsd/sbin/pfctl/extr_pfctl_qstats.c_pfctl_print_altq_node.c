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
struct TYPE_2__ {char* qname; int qid; char* ifname; scalar_t__ ifbandwidth; } ;
struct pf_altq_node {struct pf_altq_node* next; struct pf_altq_node* children; TYPE_1__ altq; } ;

/* Variables and functions */
 int PF_OPT_DEBUG ; 
 int PF_OPT_VERBOSE ; 
 int /*<<< orphan*/  pfctl_print_altq_nodestat (int,struct pf_altq_node const*) ; 
 int /*<<< orphan*/  print_altq (TYPE_1__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* rate2str (double) ; 

void
pfctl_print_altq_node(int dev, const struct pf_altq_node *node,
    unsigned int level, int opts)
{
	const struct pf_altq_node	*child;

	if (node == NULL)
		return;

	print_altq(&node->altq, level, NULL, NULL);

	if (node->children != NULL) {
		printf("{");
		for (child = node->children; child != NULL;
		    child = child->next) {
			printf("%s", child->altq.qname);
			if (child->next != NULL)
				printf(", ");
		}
		printf("}");
	}
	printf("\n");

	if (opts & PF_OPT_VERBOSE)
		pfctl_print_altq_nodestat(dev, node);

	if (opts & PF_OPT_DEBUG)
		printf("  [ qid=%u ifname=%s ifbandwidth=%s ]\n",
		    node->altq.qid, node->altq.ifname,
		    rate2str((double)(node->altq.ifbandwidth)));

	for (child = node->children; child != NULL;
	    child = child->next)
		pfctl_print_altq_node(dev, child, level + 1, opts);
}