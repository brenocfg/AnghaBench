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
struct rand_node {int /*<<< orphan*/ * next; int /*<<< orphan*/ * cp; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static struct rand_node *
rand_node_allocate(void)
{
	struct rand_node *n;

	n = (struct rand_node *)malloc(sizeof(struct rand_node));
	if (n == NULL)
		err(1, "malloc");

	n->len = 0;
	n->cp = NULL;
	n->next = NULL;
	return(n);
}