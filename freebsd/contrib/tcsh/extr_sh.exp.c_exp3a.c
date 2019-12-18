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
typedef  int tcsh_number_t ;
typedef  char Char ;

/* Variables and functions */
 scalar_t__ any (char*,char const) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 scalar_t__ compat_expr ; 
 int egetn (char*) ; 
 int /*<<< orphan*/  etracc (char*,char*,char***) ; 
 char* exp4 (char***,int) ; 
 char* putn (int) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static Char *
exp3a(Char ***vp, int ignore)
{
    Char *p1, *p2;
    const Char *op;
    tcsh_number_t i;

    p1 = exp4(vp, ignore);
    etracc("exp3a p1", p1, vp);
    op = **vp;
    if (op && any("<>", op[0]) && op[0] == op[1]) {
	(*vp)++;
	cleanup_push(p1, xfree);
	p2 = compat_expr ?
	    exp3a(vp, ignore) :
	    exp4(vp, ignore);
	cleanup_push(p2, xfree);
	etracc("exp3a p2", p2, vp);
	if (op[0] == '<')
	    i = egetn(p1) << egetn(p2);
	else
	    i = egetn(p1) >> egetn(p2);
	cleanup_until(p1);
	p1 = putn(i);
	etracc("exp3a p1", p1, vp);
    }
    return (p1);
}