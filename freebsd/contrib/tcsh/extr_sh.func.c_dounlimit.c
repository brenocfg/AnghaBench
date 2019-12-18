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
struct limits {scalar_t__ limconst; } ;
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  RLIM_TYPE ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_SILENT ; 
 int /*<<< orphan*/  ERR_ULIMUS ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 struct limits* findlim (int /*<<< orphan*/ ) ; 
 struct limits* limits ; 
 scalar_t__ setlim (struct limits*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 

void
dounlimit(Char **v, struct command *c)
{
    struct limits *lp;
    int    lerr = 0;
    int    hard = 0;
    int	   force = 0;

    USE(c);
    while (*++v && **v == '-') {
	Char   *vp = *v;
	while (*++vp)
	    switch (*vp) {
	    case 'f':
		force = 1;
		break;
	    case 'h':
		hard = 1;
		break;
	    default:
		stderror(ERR_ULIMUS);
		break;
	    }
    }

    if (*v == 0) {
	for (lp = limits; lp->limconst >= 0; lp++)
	    if (setlim(lp, hard, (RLIM_TYPE) RLIM_INFINITY) < 0)
		lerr++;
	if (!force && lerr)
	    stderror(ERR_SILENT);
	return;
    }
    while (*v) {
	lp = findlim(*v++);
	if (setlim(lp, hard, (RLIM_TYPE) RLIM_INFINITY) < 0 && !force)
	    stderror(ERR_SILENT);
    }
}