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
struct grep_pat {int token; struct grep_pat* next; } ;
struct TYPE_2__ {struct grep_expr* unary; } ;
struct grep_expr {TYPE_1__ u; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GREP_NODE_NOT ; 
#define  GREP_NOT 128 
 struct grep_expr* compile_pattern_atom (struct grep_pat**) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct grep_expr* xcalloc (int,int) ; 

__attribute__((used)) static struct grep_expr *compile_pattern_not(struct grep_pat **list)
{
	struct grep_pat *p;
	struct grep_expr *x;

	p = *list;
	if (!p)
		return NULL;
	switch (p->token) {
	case GREP_NOT:
		if (!p->next)
			die("--not not followed by pattern expression");
		*list = p->next;
		x = xcalloc(1, sizeof (struct grep_expr));
		x->node = GREP_NODE_NOT;
		x->u.unary = compile_pattern_not(list);
		if (!x->u.unary)
			die("--not followed by non pattern expression");
		return x;
	default:
		return compile_pattern_atom(list);
	}
}