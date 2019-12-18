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
typedef  int /*<<< orphan*/  tcsh_number_t ;
typedef  int Char ;

/* Variables and functions */
 int ERR_EXPRESSION ; 
 int ERR_NAME ; 
 int /*<<< orphan*/  expr (int***) ; 
 int* putn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int) ; 

__attribute__((used)) static Char *
operate(int op, Char *vp, Char *p)
{
    Char    opr[2];
    Char   *vec[5];
    Char **v = vec;
    Char  **vecp = v;
    tcsh_number_t i;

    if (op != '=') {
	if (*vp)
	    *v++ = vp;
	opr[0] = op;
	opr[1] = 0;
	*v++ = opr;
	if (op == '<' || op == '>')
	    *v++ = opr;
    }
    *v++ = p;
    *v++ = 0;
    i = expr(&vecp);
    if (*vecp)
	stderror(ERR_NAME | ERR_EXPRESSION);
    return (putn(i));
}