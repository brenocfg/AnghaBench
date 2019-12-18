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
struct roffnode {scalar_t__ tok; struct roffnode* end; struct roffnode* name; struct roffnode* parent; } ;
struct roff {struct roffnode* last; } ;

/* Variables and functions */
 scalar_t__ ROFF_while ; 
 int /*<<< orphan*/  free (struct roffnode*) ; 

__attribute__((used)) static int
roffnode_pop(struct roff *r)
{
	struct roffnode	*p;
	int		 inloop;

	p = r->last;
	inloop = p->tok == ROFF_while;
	r->last = p->parent;
	free(p->name);
	free(p->end);
	free(p);
	return inloop;
}