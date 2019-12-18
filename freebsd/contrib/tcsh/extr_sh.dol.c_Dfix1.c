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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/ ** Dfix2 (int /*<<< orphan*/ **) ; 
 int ERR_AMBIG ; 
 int ERR_NAME ; 
 int /*<<< orphan*/ * Strsave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkfree (int /*<<< orphan*/ **) ; 
 scalar_t__ noexec ; 
 int /*<<< orphan*/  setname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderror (int) ; 

Char   *
Dfix1(Char *cp)
{
    Char *Dv[2], **expanded;

    if (noexec)
	return (0);
    Dv[0] = cp;
    Dv[1] = NULL;
    expanded = Dfix2(Dv);
    if (expanded[0] == NULL || expanded[1] != NULL) {
	blkfree(expanded);
	setname(short2str(cp));
	stderror(ERR_NAME | ERR_AMBIG);
    }
    cp = Strsave(expanded[0]);
    blkfree(expanded);
    return (cp);
}