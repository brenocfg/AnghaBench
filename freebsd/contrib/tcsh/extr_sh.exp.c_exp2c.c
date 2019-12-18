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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
#define  EQEQ 131 
#define  EQMATCH 130 
 int /*<<< orphan*/  EQOP ; 
 scalar_t__ Gmatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  NOTEQ 129 
#define  NOTEQMATCH 128 
 int TEXP_IGNORE ; 
 int TEXP_NOGLOB ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 scalar_t__ egetn (int /*<<< orphan*/ *) ; 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etracc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/ * exp3 (int /*<<< orphan*/ ***,int) ; 
 scalar_t__ isa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static tcsh_number_t
exp2c(Char ***vp, int ignore)
{
    Char *p1 = exp3(vp, ignore);
    Char *p2;
    tcsh_number_t i;

    cleanup_push(p1, xfree);
    etracc("exp2c p1", p1, vp);
    if ((i = isa(**vp, EQOP)) != 0) {
	(*vp)++;
	if (i == EQMATCH || i == NOTEQMATCH)
	    ignore |= TEXP_NOGLOB;
	p2 = exp3(vp, ignore);
	cleanup_push(p2, xfree);
	etracc("exp2c p2", p2, vp);
	if (!(ignore & TEXP_IGNORE))
	    switch ((int)i) {

	    case EQEQ:
		i = eq(p1, p2);
		break;

	    case NOTEQ:
		i = !eq(p1, p2);
		break;

	    case EQMATCH:
		i = Gmatch(p1, p2);
		break;

	    case NOTEQMATCH:
		i = !Gmatch(p1, p2);
		break;
	    }
	cleanup_until(p1);
	return (i);
    }
    i = egetn(p1);
    cleanup_until(p1);
    return (i);
}