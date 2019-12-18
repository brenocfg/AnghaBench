#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int lno; scalar_t__ cno; } ;
struct TYPE_16__ {scalar_t__ searchdir; int lno; scalar_t__ cno; } ;
struct TYPE_15__ {int slno; int /*<<< orphan*/  slen; int /*<<< orphan*/ * search; } ;
struct TYPE_14__ {int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ TAGQ ;
typedef  TYPE_2__ TAG ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ MARK ;

/* Variables and functions */
 scalar_t__ FORWARD ; 
 scalar_t__ NOTSET ; 
 int SEARCH_CSCOPE ; 
 int SEARCH_FILE ; 
 int /*<<< orphan*/  TAG_BADLNO ; 
 int /*<<< orphan*/  TAG_SEARCH ; 
 int /*<<< orphan*/  db_exist (TYPE_3__*,int) ; 
 scalar_t__ f_search (TYPE_3__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nonblank (TYPE_3__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  tag_msg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cscope_search(SCR *sp, TAGQ *tqp, TAG *tp)
{
	MARK m;

	/* If we don't have a search pattern, use the line number. */
	if (tp->search == NULL) {
		if (!db_exist(sp, tp->slno)) {
			tag_msg(sp, TAG_BADLNO, tqp->tag);
			return (1);
		}
		m.lno = tp->slno;
	} else {
		/*
		 * Search for the tag; cheap fallback for C functions
		 * if the name is the same but the arguments have changed.
		 */
		m.lno = 1;
		m.cno = 0;
		if (f_search(sp, &m, &m,
		    tp->search, tp->slen, NULL, SEARCH_CSCOPE | SEARCH_FILE)) {
			tag_msg(sp, TAG_SEARCH, tqp->tag);
			return (1);
		}

		/*
		 * !!!
		 * Historically, tags set the search direction if it wasn't
		 * already set.
		 */
		if (sp->searchdir == NOTSET)
			sp->searchdir = FORWARD;
	}

	/*
	 * !!!
	 * Tags move to the first non-blank, NOT the search pattern start.
	 */
	sp->lno = m.lno;
	sp->cno = 0;
	(void)nonblank(sp, sp->lno, &sp->cno);
	return (0);
}