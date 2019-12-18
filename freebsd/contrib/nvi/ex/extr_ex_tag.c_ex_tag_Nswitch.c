#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {struct TYPE_23__* nextdisp; int /*<<< orphan*/  argv; int /*<<< orphan*/  cargv; TYPE_10__* frp; TYPE_12__* ep; int /*<<< orphan*/  gp; } ;
struct TYPE_22__ {TYPE_10__* frp; int /*<<< orphan*/  fname; } ;
struct TYPE_21__ {int /*<<< orphan*/  refcnt; } ;
struct TYPE_20__ {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ TAG ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_SCR_CENTER ; 
 int /*<<< orphan*/  SC_SCR_TOP ; 
 int /*<<< orphan*/  SC_SSWITCH ; 
 int /*<<< orphan*/  ex_buildargv (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_10__* file_add (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_end (TYPE_2__*,TYPE_12__*,int) ; 
 scalar_t__ file_init (TYPE_2__*,TYPE_10__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  screen_end (TYPE_2__*) ; 
 scalar_t__ screen_init (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  vs_discard (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vs_split (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

int
ex_tag_Nswitch(SCR *sp, TAG *tp, int force)
{
	SCR *new;

	/* Get a file structure. */
	if (tp->frp == NULL && (tp->frp = file_add(sp, tp->fname)) == NULL)
		return (1);

	/* Get a new screen. */
	if (screen_init(sp->gp, sp, &new))
		return (1);
	if (vs_split(sp, new, 0)) {
		(void)file_end(new, new->ep, 1);
		(void)screen_end(new);
		return (1);
	}

	/* Get a backing file. */
	if (tp->frp == sp->frp) {
		/* Copy file state. */
		new->ep = sp->ep;
		++new->ep->refcnt;

		new->frp = tp->frp;
		new->frp->flags = sp->frp->flags;
	} else if (file_init(new, tp->frp, NULL, force)) {
		(void)vs_discard(new, NULL);
		(void)screen_end(new);
		return (1);
	}

	/* Create the argument list. */
	new->cargv = new->argv = ex_buildargv(sp, NULL, tp->frp->name);

	/* Display tags in the center of the screen. */
	F_CLR(new, SC_SCR_TOP);
	F_SET(new, SC_SCR_CENTER);

	/* Switch. */
	sp->nextdisp = new;
	F_SET(sp, SC_SSWITCH);

	return (0);
}