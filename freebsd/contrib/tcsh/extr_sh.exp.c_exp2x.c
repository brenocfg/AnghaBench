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
 int /*<<< orphan*/  STRor ; 
 int TEXP_IGNORE ; 
 scalar_t__ compat_expr ; 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etraci (char*,int,int /*<<< orphan*/ ***) ; 
 int exp2a (int /*<<< orphan*/ ***,int) ; 

__attribute__((used)) static tcsh_number_t
exp2x(Char ***vp, int ignore)
{
    tcsh_number_t p1 = exp2a(vp, ignore);

    etraci("exp2x p1", p1, vp);
    while (**vp && eq(**vp, STRor)) {
	tcsh_number_t p2;

	(*vp)++;
	p2 = compat_expr ?
	    exp2x(vp, ignore) :
	    exp2a(vp, ignore);
	etraci("exp2x p2", p2, vp);
	if (compat_expr || !(ignore & TEXP_IGNORE))
		p1 = (p1 | p2);
	etraci("exp2x p1", p1, vp);
	if (compat_expr)
	    break;
    }
    return (p1);
}