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
struct TYPE_4__ {struct expr* expr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sym; struct expr* expr; } ;
struct expr {int type; TYPE_2__ right; TYPE_1__ left; } ;

/* Variables and functions */
#define  E_AND 129 
#define  E_OR 128 
 void* E_SYMBOL ; 
 int /*<<< orphan*/  expr_free (struct expr*) ; 
 int /*<<< orphan*/  free (struct expr*) ; 
 int /*<<< orphan*/  symbol_no ; 
 int /*<<< orphan*/  symbol_yes ; 

__attribute__((used)) static struct expr *expr_eliminate_yn(struct expr *e)
{
	struct expr *tmp;

	if (e) switch (e->type) {
	case E_AND:
		e->left.expr = expr_eliminate_yn(e->left.expr);
		e->right.expr = expr_eliminate_yn(e->right.expr);
		if (e->left.expr->type == E_SYMBOL) {
			if (e->left.expr->left.sym == &symbol_no) {
				expr_free(e->left.expr);
				expr_free(e->right.expr);
				e->type = E_SYMBOL;
				e->left.sym = &symbol_no;
				e->right.expr = NULL;
				return e;
			} else if (e->left.expr->left.sym == &symbol_yes) {
				free(e->left.expr);
				tmp = e->right.expr;
				*e = *(e->right.expr);
				free(tmp);
				return e;
			}
		}
		if (e->right.expr->type == E_SYMBOL) {
			if (e->right.expr->left.sym == &symbol_no) {
				expr_free(e->left.expr);
				expr_free(e->right.expr);
				e->type = E_SYMBOL;
				e->left.sym = &symbol_no;
				e->right.expr = NULL;
				return e;
			} else if (e->right.expr->left.sym == &symbol_yes) {
				free(e->right.expr);
				tmp = e->left.expr;
				*e = *(e->left.expr);
				free(tmp);
				return e;
			}
		}
		break;
	case E_OR:
		e->left.expr = expr_eliminate_yn(e->left.expr);
		e->right.expr = expr_eliminate_yn(e->right.expr);
		if (e->left.expr->type == E_SYMBOL) {
			if (e->left.expr->left.sym == &symbol_no) {
				free(e->left.expr);
				tmp = e->right.expr;
				*e = *(e->right.expr);
				free(tmp);
				return e;
			} else if (e->left.expr->left.sym == &symbol_yes) {
				expr_free(e->left.expr);
				expr_free(e->right.expr);
				e->type = E_SYMBOL;
				e->left.sym = &symbol_yes;
				e->right.expr = NULL;
				return e;
			}
		}
		if (e->right.expr->type == E_SYMBOL) {
			if (e->right.expr->left.sym == &symbol_no) {
				free(e->right.expr);
				tmp = e->left.expr;
				*e = *(e->left.expr);
				free(tmp);
				return e;
			} else if (e->right.expr->left.sym == &symbol_yes) {
				expr_free(e->left.expr);
				expr_free(e->right.expr);
				e->type = E_SYMBOL;
				e->left.sym = &symbol_yes;
				e->right.expr = NULL;
				return e;
			}
		}
		break;
	default:
		;
	}
	return e;
}