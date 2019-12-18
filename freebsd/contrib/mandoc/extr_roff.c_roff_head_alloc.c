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
struct roff_node {int dummy; } ;
struct roff_man {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROFFT_HEAD ; 
 int /*<<< orphan*/  ROFF_NEXT_CHILD ; 
 struct roff_node* roff_node_alloc (struct roff_man*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roff_node_append (struct roff_man*,struct roff_node*) ; 

struct roff_node *
roff_head_alloc(struct roff_man *man, int line, int pos, int tok)
{
	struct roff_node	*n;

	n = roff_node_alloc(man, line, pos, ROFFT_HEAD, tok);
	roff_node_append(man, n);
	man->next = ROFF_NEXT_CHILD;
	return n;
}