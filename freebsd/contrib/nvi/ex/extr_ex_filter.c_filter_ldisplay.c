#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ibp; int /*<<< orphan*/  ibcw; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ EX_PRIVATE ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE2INT5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  INTERRUPTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  ex_getline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ ex_ldisplay (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
filter_ldisplay(SCR *sp, FILE *fp)
{
	size_t len;
	size_t wlen;
	CHAR_T *wp;

	EX_PRIVATE *exp;

	for (exp = EXP(sp); !ex_getline(sp, fp, &len) && !INTERRUPTED(sp);) {
		FILE2INT5(sp, exp->ibcw, exp->ibp, len, wp, wlen);
		if (ex_ldisplay(sp, wp, wlen, 0, 0))
			break;
	}
	if (ferror(fp))
		msgq(sp, M_SYSERR, "filter read");
	(void)fclose(fp);
	return (0);
}