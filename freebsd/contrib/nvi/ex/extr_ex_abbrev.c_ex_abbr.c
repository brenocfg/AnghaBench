#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int argc; TYPE_1__** argv; } ;
struct TYPE_10__ {int /*<<< orphan*/  gp; } ;
struct TYPE_9__ {char* bp; int len; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXCMD ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_ABBREV ; 
 scalar_t__ ISBLANK (char) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  SEQ_ABBREV ; 
 int /*<<< orphan*/  SEQ_USERDEF ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ inword (char) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seq_dump (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ seq_set (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ex_abbr(SCR *sp, EXCMD *cmdp)
{
	CHAR_T *p;
	size_t len;

	switch (cmdp->argc) {
	case 0:
		if (seq_dump(sp, SEQ_ABBREV, 0) == 0)
			msgq(sp, M_INFO, "105|No abbreviations to display");
		return (0);
	case 2:
		break;
	default:
		abort();
	}

	/*
	 * Check for illegal characters.
	 *
	 * !!!
	 * Another fun one, historically.  See vi/v_ntext.c:txt_abbrev() for
	 * details.  The bottom line is that all abbreviations have to end
	 * with a "word" character, because it's the transition from word to
	 * non-word characters that triggers the test for an abbreviation.  In
	 * addition, because of the way the test is done, there can't be any
	 * transitions from word to non-word character (or vice-versa) other
	 * than between the next-to-last and last characters of the string,
	 * and there can't be any <blank> characters.  Warn the user.
	 */
	if (!inword(cmdp->argv[0]->bp[cmdp->argv[0]->len - 1])) {
		msgq(sp, M_ERR,
		    "106|Abbreviations must end with a \"word\" character");
			return (1);
	}
	for (p = cmdp->argv[0]->bp; *p != '\0'; ++p)
		if (ISBLANK(p[0])) {
			msgq(sp, M_ERR,
			    "107|Abbreviations may not contain tabs or spaces");
			return (1);
		}
	if (cmdp->argv[0]->len > 2)
		for (p = cmdp->argv[0]->bp,
		    len = cmdp->argv[0]->len - 2; len; --len, ++p)
			if (inword(p[0]) != inword(p[1])) {
				msgq(sp, M_ERR,
"108|Abbreviations may not mix word/non-word characters, except at the end");
				return (1);
			}

	if (seq_set(sp, NULL, 0, cmdp->argv[0]->bp, cmdp->argv[0]->len,
	    cmdp->argv[1]->bp, cmdp->argv[1]->len, SEQ_ABBREV, SEQ_USERDEF))
		return (1);

	F_SET(sp->gp, G_ABBREV);
	return (0);
}