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
struct TYPE_3__ {struct grep_expr* right; struct grep_expr* left; } ;
struct TYPE_4__ {TYPE_1__ binary; struct grep_expr* unary; } ;
struct grep_expr {int node; TYPE_2__ u; } ;

/* Variables and functions */
#define  GREP_NODE_AND 132 
#define  GREP_NODE_ATOM 131 
#define  GREP_NODE_NOT 130 
#define  GREP_NODE_OR 129 
#define  GREP_NODE_TRUE 128 
 int /*<<< orphan*/  free (struct grep_expr*) ; 

__attribute__((used)) static void free_pattern_expr(struct grep_expr *x)
{
	switch (x->node) {
	case GREP_NODE_TRUE:
	case GREP_NODE_ATOM:
		break;
	case GREP_NODE_NOT:
		free_pattern_expr(x->u.unary);
		break;
	case GREP_NODE_AND:
	case GREP_NODE_OR:
		free_pattern_expr(x->u.binary.left);
		free_pattern_expr(x->u.binary.right);
		break;
	}
	free(x);
}