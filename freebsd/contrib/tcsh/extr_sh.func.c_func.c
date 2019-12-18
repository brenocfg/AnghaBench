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
struct command {int /*<<< orphan*/  t_dcom; } ;
struct biltins {int minargs; int maxargs; int /*<<< orphan*/  (* bfunct ) (int /*<<< orphan*/ ,struct command*) ;int /*<<< orphan*/  bname; } ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_TOOFEW ; 
 int ERR_TOOMANY ; 
 int blklen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct command*) ; 
 int /*<<< orphan*/  xechoit (int /*<<< orphan*/ ) ; 

void
func(struct command *t, const struct biltins *bp)
{
    int     i;

    xechoit(t->t_dcom);
    setname(bp->bname);
    i = blklen(t->t_dcom) - 1;
    if (i < bp->minargs)
	stderror(ERR_NAME | ERR_TOOFEW);
    if (i > bp->maxargs)
	stderror(ERR_NAME | ERR_TOOMANY);
    (*bp->bfunct) (t->t_dcom, t);
}