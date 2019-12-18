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
struct headline {int /*<<< orphan*/ * l_date; int /*<<< orphan*/ * l_tty; int /*<<< orphan*/ * l_from; } ;

/* Variables and functions */
 int LINESIZE ; 
 void* copyin (char*,char**) ; 
 scalar_t__ isdate (char*) ; 
 char* nextword (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
parse(char line[], struct headline *hl, char pbuf[])
{
	char *cp, *sp;
	char word[LINESIZE];

	hl->l_from = NULL;
	hl->l_tty = NULL;
	hl->l_date = NULL;
	cp = line;
	sp = pbuf;
	/*
	 * Skip over "From" first.
	 */
	cp = nextword(cp, word);
	/*
	 * Check for missing return-path.
	 */
	if (isdate(cp)) {
		hl->l_date = copyin(cp, &sp);
		return;
	}
	cp = nextword(cp, word);
	if (strlen(word) > 0)
		hl->l_from = copyin(word, &sp);
	if (cp != NULL && strncmp(cp, "tty", 3) == 0) {
		cp = nextword(cp, word);
		hl->l_tty = copyin(word, &sp);
	}
	if (cp != NULL)
		hl->l_date = copyin(cp, &sp);
}