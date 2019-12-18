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
typedef  scalar_t__ tcsh_number_t ;
typedef  int Char ;

/* Variables and functions */
 int /*<<< orphan*/  ADDOP ; 
 int TEXP_IGNORE ; 
 int /*<<< orphan*/  cleanup_push (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int*) ; 
 scalar_t__ compat_expr ; 
 scalar_t__ egetn (int*) ; 
 int /*<<< orphan*/  etracc (char*,int*,int***) ; 
 int* exp5 (int***,int) ; 
 scalar_t__ isa (int*,int /*<<< orphan*/ ) ; 
 int* putn (scalar_t__) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static Char *
exp4(Char ***vp, int ignore)
{
    Char *p1, *p2;
    tcsh_number_t i = 0;

    p1 = exp5(vp, ignore);
    etracc("exp4 p1", p1, vp);
    while (isa(**vp, ADDOP)) {
	const Char *op = *(*vp)++;

	cleanup_push(p1, xfree);
	p2 = compat_expr ?
	    exp4(vp, ignore) :
	    exp5(vp, ignore);
	cleanup_push(p2, xfree);
	etracc("exp4 p2", p2, vp);
	if (!(ignore & TEXP_IGNORE))
	    switch (op[0]) {

	    case '+':
		i = egetn(p1) + egetn(p2);
		break;

	    case '-':
		i = egetn(p1) - egetn(p2);
		break;
	    }
	cleanup_until(p1);
	p1 = putn(i);
	etracc("exp4 p1", p1, vp);
	if (compat_expr)
	    break;
    }
    return (p1);
}