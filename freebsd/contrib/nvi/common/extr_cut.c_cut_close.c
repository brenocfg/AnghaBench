#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  textq; } ;
struct TYPE_6__ {TYPE_2__ dcb_store; int /*<<< orphan*/  cutq; } ;
typedef  TYPE_1__ GS ;
typedef  TYPE_2__ CB ;

/* Variables and functions */
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  text_lfree (int /*<<< orphan*/ ) ; 

void
cut_close(GS *gp)
{
	CB *cbp;

	/* Free cut buffer list. */
	while ((cbp = SLIST_FIRST(gp->cutq)) != NULL) {
		if (!TAILQ_EMPTY(cbp->textq))
			text_lfree(cbp->textq);
		SLIST_REMOVE_HEAD(gp->cutq, q);
		free(cbp);
	}

	/* Free default cut storage. */
	cbp = &gp->dcb_store;
	if (!TAILQ_EMPTY(cbp->textq))
		text_lfree(cbp->textq);
}