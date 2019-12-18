#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int lno; scalar_t__ cno; } ;
struct TYPE_11__ {scalar_t__ searchdir; int lno; scalar_t__ cno; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ MARK ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ FORWARD ; 
 int /*<<< orphan*/  INT2CHAR (TYPE_1__*,int /*<<< orphan*/ *,size_t,char*,size_t) ; 
 scalar_t__ ISDIGIT (int /*<<< orphan*/ ) ; 
 scalar_t__ NOTSET ; 
 int SEARCH_FILE ; 
 int SEARCH_TAG ; 
 int /*<<< orphan*/  TAG_BADLNO ; 
 int /*<<< orphan*/  TAG_SEARCH ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  db_exist (TYPE_1__*,int) ; 
 scalar_t__ f_search (TYPE_1__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nonblank (TYPE_1__*,int,scalar_t__*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  tag_msg (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ctag_search(SCR *sp, CHAR_T *search, size_t slen, char *tag)
{
	MARK m;
	char *p;
	char *np;
	size_t nlen;

	/*
	 * !!!
	 * The historic tags file format (from a long, long time ago...)
	 * used a line number, not a search string.  I got complaints, so
	 * people are still using the format.  POSIX 1003.2 permits it.
	 */
	if (ISDIGIT(search[0])) {
		INT2CHAR(sp, search, slen+1, np, nlen);
		m.lno = atoi(np);
		if (!db_exist(sp, m.lno)) {
			tag_msg(sp, TAG_BADLNO, tag);
			return (1);
		}
	} else {
		/*
		 * Search for the tag; cheap fallback for C functions
		 * if the name is the same but the arguments have changed.
		 */
		m.lno = 1;
		m.cno = 0;
		if (f_search(sp, &m, &m,
		    search, slen, NULL, SEARCH_FILE | SEARCH_TAG)) {
			INT2CHAR(sp, search, slen, np, nlen);
			if ((p = strrchr(np, '(')) != NULL) {
				slen = p - np;
				if (f_search(sp, &m, &m, search, slen,
				    NULL, SEARCH_FILE | SEARCH_TAG))
					goto notfound;
			} else {
notfound:			tag_msg(sp, TAG_SEARCH, tag);
				return (1);
			}
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