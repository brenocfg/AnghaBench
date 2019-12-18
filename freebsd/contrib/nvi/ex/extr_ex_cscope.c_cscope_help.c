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
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*,size_t) ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 int csc_help (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
cscope_help(SCR *sp, EXCMD *cmdp, CHAR_T *subcmd)
{
	char *np;
	size_t nlen;

	INT2CHAR(sp, subcmd, STRLEN(subcmd) + 1, np, nlen);
	return (csc_help(sp, np));
}