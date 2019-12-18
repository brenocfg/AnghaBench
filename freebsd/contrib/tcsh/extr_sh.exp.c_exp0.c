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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  STRor2 ; 
 int TEXP_IGNORE ; 
 scalar_t__ compat_expr ; 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etraci (char*,int,int /*<<< orphan*/ ***) ; 
 int exp1 (int /*<<< orphan*/ ***,int) ; 

tcsh_number_t
exp0(Char ***vp, int ignore)
{
    tcsh_number_t p1 = exp1(vp, ignore);

    etraci("exp0 p1", p1, vp);
    while (**vp && eq(**vp, STRor2)) {
	int p2;

	(*vp)++;

	p2 = compat_expr ? 
	    exp0(vp, (ignore & TEXP_IGNORE) || p1) :
	    exp1(vp, (ignore & TEXP_IGNORE) || p1);
	if (compat_expr || !(ignore & TEXP_IGNORE))
	    p1 = (p1 || p2);
	etraci("exp0 p1", p1, vp);
	if (compat_expr)
	    break;
    }
    return (p1);
}