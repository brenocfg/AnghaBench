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
struct TYPE_2__ {int* p_stack; size_t tos; int /*<<< orphan*/ * il; int /*<<< orphan*/  i_l_follow; int /*<<< orphan*/ * cstk; } ;

/* Variables and functions */
 int /*<<< orphan*/  case_ind ; 
#define  decl 136 
 int dohead ; 
#define  dolit 135 
#define  elsehead 134 
#define  forstmt 133 
 int ifhead ; 
#define  ifstmt 132 
 int const lbrace ; 
 TYPE_1__ ps ; 
#define  stmt 131 
#define  stmtl 130 
#define  swstmt 129 
#define  whilestmt 128 

__attribute__((used)) static void
reduce(void)
{
    int i;

    for (;;) {			/* keep looping until there is nothing left to
				 * reduce */

	switch (ps.p_stack[ps.tos]) {

	case stmt:
	    switch (ps.p_stack[ps.tos - 1]) {

	    case stmt:
	    case stmtl:
		/* stmtl stmt or stmt stmt */
		ps.p_stack[--ps.tos] = stmtl;
		break;

	    case dolit:	/* <do> <stmt> */
		ps.p_stack[--ps.tos] = dohead;
		ps.i_l_follow = ps.il[ps.tos];
		break;

	    case ifstmt:
		/* <if> <stmt> */
		ps.p_stack[--ps.tos] = ifhead;
		for (i = ps.tos - 1;
			(
			 ps.p_stack[i] != stmt
			 &&
			 ps.p_stack[i] != stmtl
			 &&
			 ps.p_stack[i] != lbrace
			 );
			--i);
		ps.i_l_follow = ps.il[i];
		/*
		 * for the time being, we will assume that there is no else on
		 * this if, and set the indentation level accordingly. If an
		 * else is scanned, it will be fixed up later
		 */
		break;

	    case swstmt:
		/* <switch> <stmt> */
		case_ind = ps.cstk[ps.tos - 1];
		/* FALLTHROUGH */
	    case decl:		/* finish of a declaration */
	    case elsehead:
		/* <<if> <stmt> else> <stmt> */
	    case forstmt:
		/* <for> <stmt> */
	    case whilestmt:
		/* <while> <stmt> */
		ps.p_stack[--ps.tos] = stmt;
		ps.i_l_follow = ps.il[ps.tos];
		break;

	    default:		/* <anything else> <stmt> */
		return;

	    }			/* end of section for <stmt> on top of stack */
	    break;

	case whilestmt:	/* while (...) on top */
	    if (ps.p_stack[ps.tos - 1] == dohead) {
		/* it is termination of a do while */
		ps.tos -= 2;
		break;
	    }
	    else
		return;

	default:		/* anything else on top */
	    return;

	}
    }
}