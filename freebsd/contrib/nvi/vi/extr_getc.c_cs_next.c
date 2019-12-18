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
struct TYPE_3__ {int cs_flags; size_t cs_cno; int /*<<< orphan*/ * cs_bp; int /*<<< orphan*/  cs_ch; int /*<<< orphan*/  cs_len; int /*<<< orphan*/  cs_lno; } ;
typedef  TYPE_1__ VCS ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
#define  CS_EMP 130 
#define  CS_EOF 129 
#define  CS_EOL 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  db_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_isempty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
cs_next(SCR *sp, VCS *csp)
{
	CHAR_T *p;

	switch (csp->cs_flags) {
	case CS_EMP:				/* EMP; get next line. */
	case CS_EOL:				/* EOL; get next line. */
		if (db_get(sp, ++csp->cs_lno, 0, &p, &csp->cs_len)) {
			--csp->cs_lno;
			csp->cs_flags = CS_EOF;
		} else {
			csp->cs_bp = p;
			if (csp->cs_len == 0 ||
			    v_isempty(csp->cs_bp, csp->cs_len)) {
				csp->cs_cno = 0;
				csp->cs_flags = CS_EMP;
			} else {
				csp->cs_flags = 0;
				csp->cs_ch = csp->cs_bp[csp->cs_cno = 0];
			}
		}
		break;
	case 0:
		if (csp->cs_cno == csp->cs_len - 1)
			csp->cs_flags = CS_EOL;
		else
			csp->cs_ch = csp->cs_bp[++csp->cs_cno];
		break;
	case CS_EOF:				/* EOF. */
		break;
	default:
		abort();
		/* NOTREACHED */
	}
	return (0);
}