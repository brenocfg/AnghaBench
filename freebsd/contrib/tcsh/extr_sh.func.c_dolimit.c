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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_SILENT ; 
 int /*<<< orphan*/  STRmh ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct limits* findlim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getval (struct limits*,int /*<<< orphan*/ **) ; 
 struct limits* limits ; 
 int /*<<< orphan*/  plim (struct limits*,int) ; 
 scalar_t__ setlim (struct limits*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 

void
dolimit(Char **v, struct command *c)
{
    struct limits *lp;
    RLIM_TYPE limit;
    int    hard = 0;

    USE(c);
    v++;
    if (*v && eq(*v, STRmh)) {
	hard = 1;
	v++;
    }
    if (*v == 0) {
	for (lp = limits; lp->limconst >= 0; lp++)
	    plim(lp, hard);
	return;
    }
    lp = findlim(v[0]);
    if (v[1] == 0) {
	plim(lp, hard);
	return;
    }
    limit = getval(lp, v + 1);
    if (setlim(lp, hard, limit) < 0)
	stderror(ERR_SILENT);
}