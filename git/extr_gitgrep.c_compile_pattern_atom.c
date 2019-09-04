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
struct TYPE_2__ {struct grep_pat* atom; } ;
struct grep_expr {TYPE_1__ u; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int GREP_CLOSE_PAREN ; 
 int /*<<< orphan*/  GREP_NODE_ATOM ; 
#define  GREP_OPEN_PAREN 131 
#define  GREP_PATTERN 130 
#define  GREP_PATTERN_BODY 129 
#define  GREP_PATTERN_HEAD 128 
 struct grep_expr* compile_pattern_or (struct grep_pat**) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct grep_expr* xcalloc (int,int) ; 

__attribute__((used)) static struct grep_expr *compile_pattern_atom(struct grep_pat **list)
{
	struct grep_pat *p;
	struct grep_expr *x;

	p = *list;
	if (!p)
		return NULL;
	switch (p->token) {
	case GREP_PATTERN: /* atom */
	case GREP_PATTERN_HEAD:
	case GREP_PATTERN_BODY:
		x = xcalloc(1, sizeof (struct grep_expr));
		x->node = GREP_NODE_ATOM;
		x->u.atom = p;
		*list = p->next;
		return x;
	case GREP_OPEN_PAREN:
		*list = p->next;
		x = compile_pattern_or(list);
		if (!*list || (*list)->token != GREP_CLOSE_PAREN)
			die("unmatched parenthesis");
		*list = (*list)->next;
		return x;
	default:
		return NULL;
	}
}