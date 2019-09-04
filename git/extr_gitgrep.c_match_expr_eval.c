#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct grep_opt {int /*<<< orphan*/  columnnum; } ;
struct TYPE_5__ {struct grep_expr* right; struct grep_expr* left; } ;
struct TYPE_6__ {TYPE_1__ binary; struct grep_expr* unary; int /*<<< orphan*/  atom; } ;
struct grep_expr {int node; int hit; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  rm_so; } ;
typedef  TYPE_3__ regmatch_t ;
typedef  enum grep_context { ____Placeholder_grep_context } grep_context ;

/* Variables and functions */
#define  GREP_NODE_AND 132 
#define  GREP_NODE_ATOM 131 
#define  GREP_NODE_NOT 130 
#define  GREP_NODE_OR 129 
#define  GREP_NODE_TRUE 128 
 int /*<<< orphan*/  die (char*,...) ; 
 int match_one_pattern (int /*<<< orphan*/ ,char*,char*,int,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_expr_eval(struct grep_opt *opt, struct grep_expr *x, char *bol,
			   char *eol, enum grep_context ctx, ssize_t *col,
			   ssize_t *icol, int collect_hits)
{
	int h = 0;

	if (!x)
		die("Not a valid grep expression");
	switch (x->node) {
	case GREP_NODE_TRUE:
		h = 1;
		break;
	case GREP_NODE_ATOM:
		{
			regmatch_t tmp;
			h = match_one_pattern(x->u.atom, bol, eol, ctx,
					      &tmp, 0);
			if (h && (*col < 0 || tmp.rm_so < *col))
				*col = tmp.rm_so;
		}
		break;
	case GREP_NODE_NOT:
		/*
		 * Upon visiting a GREP_NODE_NOT, col and icol become swapped.
		 */
		h = !match_expr_eval(opt, x->u.unary, bol, eol, ctx, icol, col,
				     0);
		break;
	case GREP_NODE_AND:
		h = match_expr_eval(opt, x->u.binary.left, bol, eol, ctx, col,
				    icol, 0);
		if (h || opt->columnnum) {
			/*
			 * Don't short-circuit AND when given --column, since a
			 * NOT earlier in the tree may turn this into an OR. In
			 * this case, see the below comment.
			 */
			h &= match_expr_eval(opt, x->u.binary.right, bol, eol,
					     ctx, col, icol, 0);
		}
		break;
	case GREP_NODE_OR:
		if (!(collect_hits || opt->columnnum)) {
			/*
			 * Don't short-circuit OR when given --column (or
			 * collecting hits) to ensure we don't skip a later
			 * child that would produce an earlier match.
			 */
			return (match_expr_eval(opt, x->u.binary.left, bol, eol,
						ctx, col, icol, 0) ||
				match_expr_eval(opt, x->u.binary.right, bol,
						eol, ctx, col, icol, 0));
		}
		h = match_expr_eval(opt, x->u.binary.left, bol, eol, ctx, col,
				    icol, 0);
		if (collect_hits)
			x->u.binary.left->hit |= h;
		h |= match_expr_eval(opt, x->u.binary.right, bol, eol, ctx, col,
				     icol, collect_hits);
		break;
	default:
		die("Unexpected node type (internal error) %d", x->node);
	}
	if (collect_hits)
		x->hit |= h;
	return h;
}