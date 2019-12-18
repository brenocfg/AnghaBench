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
struct expression {int type; struct expression* next; } ;

/* Variables and functions */
#define  TYPE_OP_DIVIDE 135 
#define  TYPE_OP_MINUS 134 
#define  TYPE_OP_MULT 133 
#define  TYPE_OP_PLUS 132 
#define  TYPE_PARN_CLOSE 131 
#define  TYPE_PARN_OPEN 130 
#define  TYPE_VALUE_CON 129 
#define  TYPE_VALUE_PMC 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
validate_expr(struct expression *exp, int val1_is_set, int op_is_set, int val2_is_set, 
	      int *op_cnt)
{
	int val1, op, val2;
	int open_cnt;
	val1 = op = val2 = 0;
	if (val1_is_set) {
		val1 = 1;
	}
	if (op_is_set) {
		op = 1;
	}
	if (val2_is_set) {
		val2 = 1;
	}
	open_cnt = *op_cnt;
	if (exp == NULL) {
		/* End of the road */
		if (val1 && op && val2 && (open_cnt == 0)) {
			return(0);
		} else {
			return(1);
		}
	}
	switch(exp->type) {
	case TYPE_OP_PLUS:
	case TYPE_OP_MINUS:
	case TYPE_OP_MULT:
	case TYPE_OP_DIVIDE:
		if (val1 && op && val2) {
			/* We are at x + y + 
			 * collapse back to val/op
			 */
			val1 = 1;
			op = 1;
			val2 = 0;
		} else if ((op == 0) && (val1)) {
			op = 1;
		} else {
			printf("Op but no val1 set\n");
			return(-1);
		}
		break;
	case TYPE_PARN_OPEN:
		if (exp->next == NULL) {
			printf("NULL after open paren\n");
			exit(-1);
		}
		if ((exp->next->type == TYPE_OP_PLUS) ||
		    (exp->next->type == TYPE_OP_MINUS) ||
		    (exp->next->type == TYPE_OP_DIVIDE) ||
		    (exp->next->type == TYPE_OP_MULT)) {
			printf("'( OP' -- not allowed\n");
			return(-1);
		}
		if (val1 && (op == 0)) {
			printf("'Val (' -- not allowed\n");
			return(-1);
		}
		if (val1 && op && val2) {
			printf("'Val OP Val (' -- not allowed\n");
			return(-1);
		}
		open_cnt++;
		*op_cnt = open_cnt;
		if (val1) {
			if (validate_expr(exp->next, 0, 0, 0, op_cnt) == 0) {
				val2 = 1;
			} else {
				return(-1);
			}
		} else {
			return(validate_expr(exp->next, 0, 0, 0, op_cnt));
		}
		break;
	case TYPE_PARN_CLOSE:
		open_cnt--;
		*op_cnt = open_cnt;
		if (val1 && op && val2) {
			return(0);
		} else {
			printf("Found close paren and not complete\n");
			return(-1);
		}
		break;
	case TYPE_VALUE_CON:
	case TYPE_VALUE_PMC:
		if (val1 == 0) {
			val1 = 1;
		} else if (val1 && op) {
			val2 = 1;
		} else {
			printf("val1 set, val2 about to be set op empty\n");
			return(-1);
		}
		break;
	default:
		printf("unknown type %d\n", exp->type);
		exit(-5);
		break;
	}
	return(validate_expr(exp->next, val1, op, val2, op_cnt));
}