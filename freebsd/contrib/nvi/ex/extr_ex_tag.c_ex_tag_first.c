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
 int /*<<< orphan*/  C_TAG ; 
 int /*<<< orphan*/  F_CLR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OOBLNO ; 
 int /*<<< orphan*/  SC_SCR_CENTER ; 
 int /*<<< orphan*/  SC_SCR_TOP ; 
 int /*<<< orphan*/  STRLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_exp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_cinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ex_tag_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ex_tag_first(SCR *sp, CHAR_T *tagarg)
{
	EXCMD cmd;

	/* Build an argument for the ex :tag command. */
	ex_cinit(sp, &cmd, C_TAG, 0, OOBLNO, OOBLNO, 0);
	argv_exp0(sp, &cmd, tagarg, STRLEN(tagarg));

	/*
	 * XXX
	 * Historic vi went ahead and created a temporary file when it failed
	 * to find the tag.  We match historic practice, but don't distinguish
	 * between real error and failure to find the tag.
	 */
	if (ex_tag_push(sp, &cmd))
		return (0);

	/* Display tags in the center of the screen. */
	F_CLR(sp, SC_SCR_TOP);
	F_SET(sp, SC_SCR_CENTER);

	return (0);
}