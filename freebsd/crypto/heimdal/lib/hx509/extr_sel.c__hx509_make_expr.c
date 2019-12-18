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
struct hx_expr {int op; void* arg2; void* arg1; } ;
typedef  enum hx_expr_op { ____Placeholder_hx_expr_op } hx_expr_op ;

/* Variables and functions */
 struct hx_expr* malloc (int) ; 

struct hx_expr *
_hx509_make_expr(enum hx_expr_op op, void *arg1, void *arg2)
{
    struct hx_expr *expr;

    expr = malloc(sizeof(*expr));
    if (expr == NULL)
	return NULL;
    expr->op = op;
    expr->arg1 = arg1;
    expr->arg2 = arg2;

    return expr;
}