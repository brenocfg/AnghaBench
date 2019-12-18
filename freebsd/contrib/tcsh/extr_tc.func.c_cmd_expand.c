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
struct wordent {int /*<<< orphan*/ * word; struct wordent* prev; struct wordent* next; } ;
struct varent {int /*<<< orphan*/ * vec; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/ * STRNULL ; 
 int /*<<< orphan*/ * STRret ; 
 int TRUE ; 
 struct varent* adrof1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aliases ; 
 int /*<<< orphan*/ * blkexpand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkpr (int /*<<< orphan*/ *) ; 
 int tellmewhat (struct wordent*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xputchar (char) ; 

int
cmd_expand(Char *cmd, Char **str)
{
    struct wordent lexp[3];
    struct varent *vp;
    int rv = TRUE;

    lexp[0].next = &lexp[1];
    lexp[1].next = &lexp[2];
    lexp[2].next = &lexp[0];

    lexp[0].prev = &lexp[2];
    lexp[1].prev = &lexp[0];
    lexp[2].prev = &lexp[1];

    lexp[0].word = STRNULL;
    lexp[2].word = STRret;

    if ((vp = adrof1(cmd, &aliases)) != NULL && vp->vec != NULL) {
	if (str == NULL) {
	    xprintf(CGETS(22, 1, "%S: \t aliased to "), cmd);
	    blkpr(vp->vec);
	    xputchar('\n');
	}
	else
	    *str = blkexpand(vp->vec);
    }
    else {
	lexp[1].word = cmd;
	rv = tellmewhat(lexp, str);
    }
    return rv;
}