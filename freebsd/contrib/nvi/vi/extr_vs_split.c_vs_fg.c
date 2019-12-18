#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  hq; int /*<<< orphan*/  dq; } ;
struct TYPE_15__ {TYPE_2__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ GS ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  INT2CHAR (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq_wstr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  q ; 
 TYPE_1__* vs_getbg (TYPE_1__*,char*) ; 
 scalar_t__ vs_split (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vs_swap (TYPE_1__*,TYPE_1__**,char*) ; 

int
vs_fg(SCR *sp, SCR **nspp, CHAR_T *name, int newscreen)
{
	GS *gp;
	SCR *nsp;
	char *np;
	size_t nlen;

	gp = sp->gp;

	if (name)
	    INT2CHAR(sp, name, STRLEN(name) + 1, np, nlen);
	else
	    np = NULL;
	if (newscreen)
		/* Get the specified background screen. */
		nsp = vs_getbg(sp, np);
	else
		/* Swap screens. */
		if (vs_swap(sp, &nsp, np))
			return (1);

	if ((*nspp = nsp) == NULL) {
		msgq_wstr(sp, M_ERR, name,
		    name == NULL ?
		    "223|There are no background screens" :
		    "224|There's no background screen editing a file named %s");
		return (1);
	}

	if (newscreen) {
		/* Remove the new screen from the background queue. */
		TAILQ_REMOVE(gp->hq, nsp, q);

		/* Split the screen; if we fail, hook the screen back in. */
		if (vs_split(sp, nsp, 0)) {
			TAILQ_INSERT_TAIL(gp->hq, nsp, q);
			return (1);
		}
	} else {
		/* Move the old screen to the background queue. */
		TAILQ_REMOVE(gp->dq, sp, q);
		TAILQ_INSERT_TAIL(gp->hq, sp, q);
	}
	return (0);
}