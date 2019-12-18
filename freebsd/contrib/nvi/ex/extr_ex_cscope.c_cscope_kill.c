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
typedef  scalar_t__ CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,scalar_t__*,scalar_t__,char*,size_t) ; 
 scalar_t__ STRLEN (scalar_t__*) ; 
 int atoi (char*) ; 
 int terminate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
cscope_kill(SCR *sp, EXCMD *cmdp, CHAR_T *cn)
{
	char *np;
	size_t nlen;
	int n = 1;

	if (*cn) {
		INT2CHAR(sp, cn, STRLEN(cn) + 1, np, nlen);
		n = atoi(np);
	}
	return (terminate(sp, NULL, n));
}