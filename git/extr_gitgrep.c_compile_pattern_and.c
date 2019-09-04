#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grep_pat {scalar_t__ token; struct grep_pat* next; } ;
struct TYPE_3__ {struct grep_expr* right; struct grep_expr* left; } ;
struct TYPE_4__ {TYPE_1__ binary; } ;
struct grep_expr {TYPE_2__ u; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__ GREP_AND ; 
 int /*<<< orphan*/  GREP_NODE_AND ; 
 struct grep_expr* compile_pattern_not (struct grep_pat**) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct grep_expr* xcalloc (int,int) ; 

__attribute__((used)) static struct grep_expr *compile_pattern_and(struct grep_pat **list)
{
	struct grep_pat *p;
	struct grep_expr *x, *y, *z;

	x = compile_pattern_not(list);
	p = *list;
	if (p && p->token == GREP_AND) {
		if (!p->next)
			die("--and not followed by pattern expression");
		*list = p->next;
		y = compile_pattern_and(list);
		if (!y)
			die("--and not followed by pattern expression");
		z = xcalloc(1, sizeof (struct grep_expr));
		z->node = GREP_NODE_AND;
		z->u.binary.left = x;
		z->u.binary.right = y;
		return z;
	}
	return x;
}