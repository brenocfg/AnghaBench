#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VICMD ;
struct TYPE_9__ {char* alt_name; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  EXCMD ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR2INT (TYPE_1__*,char*,scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  C_EDIT ; 
 int /*<<< orphan*/  FS_ALL ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  OOBLNO ; 
 int /*<<< orphan*/  argv_exp0 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ex_cinit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ file_m1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 int v_exec_ex (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
v_switch(SCR *sp, VICMD *vp)
{
	EXCMD cmd;
	char *name;
	CHAR_T *wp;
	size_t wlen;

	/*
	 * Try the alternate file name, then the previous file
	 * name.  Use the real name, not the user's current name.
	 */
	if ((name = sp->alt_name) == NULL) {
		msgq(sp, M_ERR, "180|No previous file to edit");
		return (1);
	}

	/* If autowrite is set, write out the file. */
	if (file_m1(sp, 0, FS_ALL))
		return (1);

	ex_cinit(sp, &cmd, C_EDIT, 0, OOBLNO, OOBLNO, 0);
	CHAR2INT(sp, name, strlen(name) + 1, wp, wlen);
	argv_exp0(sp, &cmd, wp, wlen);
	return (v_exec_ex(sp, vp, &cmd));
}