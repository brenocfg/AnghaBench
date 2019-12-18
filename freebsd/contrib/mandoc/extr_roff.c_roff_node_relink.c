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
struct roff_node {int /*<<< orphan*/ * next; int /*<<< orphan*/  prev; } ;
struct roff_man {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  roff_node_append (struct roff_man*,struct roff_node*) ; 
 int /*<<< orphan*/  roff_node_unlink (struct roff_man*,struct roff_node*) ; 

void
roff_node_relink(struct roff_man *man, struct roff_node *n)
{
	roff_node_unlink(man, n);
	n->prev = n->next = NULL;
	roff_node_append(man, n);
}