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
struct roff_node {struct roff_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  md_node (struct roff_node*) ; 

__attribute__((used)) static void
md_nodelist(struct roff_node *n)
{
	while (n != NULL) {
		md_node(n);
		n = n->next;
	}
}