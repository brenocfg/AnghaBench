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
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  EXCMD ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR2INT (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  FREE_SPACE (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  GET_SPACE_RETC (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 int /*<<< orphan*/  cscope_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
start_cscopes(SCR *sp, EXCMD *cmdp)
{
	size_t blen, len;
	char *bp, *cscopes, *p, *t;
	CHAR_T *wp;
	size_t wlen;

	/*
	 * EXTENSION #1:
	 *
	 * If the CSCOPE_DIRS environment variable is set, we treat it as a
	 * list of cscope directories that we're using, similar to the tags
	 * edit option.
	 *
	 * XXX
	 * This should probably be an edit option, although that implies that
	 * we start/stop cscope processes periodically, instead of once when
	 * the editor starts.
	 */
	if ((cscopes = getenv("CSCOPE_DIRS")) == NULL)
		return (0);
	len = strlen(cscopes);
	GET_SPACE_RETC(sp, bp, blen, len);
	memcpy(bp, cscopes, len + 1);

	for (cscopes = t = bp; (p = strsep(&t, "\t :")) != NULL;)
		if (*p != '\0') {
			CHAR2INT(sp, p, strlen(p) + 1, wp, wlen);
			(void)cscope_add(sp, cmdp, wp);
		}

	FREE_SPACE(sp, bp, blen);
	return (0);
}