#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t argc; TYPE_1__** argv; } ;
struct TYPE_7__ {size_t argsoff; TYPE_1__** args; } ;
struct TYPE_6__ {char* bp; size_t len; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EX_PRIVATE ;
typedef  TYPE_3__ EXCMD ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 TYPE_2__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEMCPY (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  argv_alloc (int /*<<< orphan*/ *,size_t) ; 

int
argv_exp0(SCR *sp, EXCMD *excp, CHAR_T *cmd, size_t cmdlen)
{
	EX_PRIVATE *exp;

	exp = EXP(sp);
	argv_alloc(sp, cmdlen);
	MEMCPY(exp->args[exp->argsoff]->bp, cmd, cmdlen);
	exp->args[exp->argsoff]->bp[cmdlen] = '\0';
	exp->args[exp->argsoff]->len = cmdlen;
	++exp->argsoff;
	excp->argv = exp->args;
	excp->argc = exp->argsoff;
	return (0);
}