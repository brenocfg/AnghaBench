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
typedef  int /*<<< orphan*/  exm_t ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  STRLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ex_emsg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
ex_wemsg(SCR* sp, CHAR_T *p, exm_t which)
{
	char *np;
	size_t nlen;

	if (p) INT2CHAR(sp, p, STRLEN(p), np, nlen);
	else np = NULL;
	ex_emsg(sp, np, which);
}