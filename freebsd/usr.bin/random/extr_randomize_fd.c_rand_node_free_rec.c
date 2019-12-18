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
struct rand_node {struct rand_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  rand_node_free (struct rand_node*) ; 

__attribute__((used)) static void
rand_node_free_rec(struct rand_node *n)
{
	if (n != NULL) {
		if (n->next != NULL)
			rand_node_free_rec(n->next);

		rand_node_free(n);
	}
}