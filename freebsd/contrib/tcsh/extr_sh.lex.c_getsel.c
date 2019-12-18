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
typedef  int eChar ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_BADBANGARG ; 
 int /*<<< orphan*/  Isdigit (int) ; 
 scalar_t__ any (char*,int) ; 
 int getC (int /*<<< orphan*/ ) ; 
 int quesarg ; 
 int /*<<< orphan*/  seterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unreadc (int) ; 

__attribute__((used)) static int
getsel(int *al, int *ar, int dol)
{
    eChar c = getC(0);
    int i;
    int    first = *al < 0;

    switch (c) {

    case '%':
	if (quesarg == -1) {
	    seterror(ERR_BADBANGARG);
	    return (0);
	}
	if (*al < 0)
	    *al = quesarg;
	*ar = quesarg;
	break;

    case '-':
	if (*al < 0) {
	    *al = 0;
	    *ar = dol - 1;
	    unreadc(c);
	}
	return (1);

    case '^':
	if (*al < 0)
	    *al = 1;
	*ar = 1;
	break;

    case '$':
	if (*al < 0)
	    *al = dol;
	*ar = dol;
	break;

    case '*':
	if (*al < 0)
	    *al = 1;
	*ar = dol;
	if (*ar < *al) {
	    *ar = 0;
	    *al = 1;
	    return (1);
	}
	break;

    default:
	if (Isdigit(c)) {
	    i = 0;
	    while (Isdigit(c)) {
		i = i * 10 + c - '0';
		c = getC(0);
	    }
	    if (i < 0)
		i = dol + 1;
	    if (*al < 0)
		*al = i;
	    *ar = i;
	}
	else if (*al < 0)
	    *al = 0, *ar = dol;
	else
	    *ar = dol - 1;
	unreadc(c);
	break;
    }
    if (first) {
	c = getC(0);
	unreadc(c);
	if (any("-$*", c))
	    return (1);
    }
    if (*al > *ar || *ar > dol) {
	seterror(ERR_BADBANGARG);
	return (0);
    }
    return (1);

}