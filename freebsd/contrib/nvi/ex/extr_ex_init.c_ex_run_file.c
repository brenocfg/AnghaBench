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
 int /*<<< orphan*/  CHAR2INT (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  C_SOURCE ; 
 int /*<<< orphan*/  OOBLNO ; 
 int /*<<< orphan*/  argv_exp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ex_cinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ex_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
ex_run_file(SCR *sp, char *name)
{
	EXCMD cmd;
	CHAR_T *wp;
	size_t wlen;

	ex_cinit(sp, &cmd, C_SOURCE, 0, OOBLNO, OOBLNO, 0);
	CHAR2INT(sp, name, strlen(name)+1, wp, wlen);
	argv_exp0(sp, &cmd, wp, wlen - 1);
	return (ex_source(sp, &cmd));
}