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
struct expression {scalar_t__ type; struct expression* next; } ;

/* Variables and functions */
 scalar_t__ TYPE_PARN_OPEN ; 
 double run_expr (struct expression*,int /*<<< orphan*/ ,struct expression**) ; 

__attribute__((used)) static struct expression *
gather_exp_to_paren_close(struct expression *exp, double *val_fill)
{
	/*
	 * I have been given ( ???
	 * so I could see either
	 * (
	 * or
	 * Val Op
	 *
	 */
	struct expression *lastproc;
	double val;

	if (exp->type == TYPE_PARN_OPEN) {
		lastproc = gather_exp_to_paren_close(exp->next, &val);
		*val_fill = val;
	} else {
		*val_fill = run_expr(exp, 0, &lastproc);
	}
	return(lastproc);
}