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
struct TYPE_3__ {char* ibp; size_t ibp_len; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ EX_PRIVATE ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_RETC (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 scalar_t__ EINTR ; 
 int EOF ; 
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 

int
ex_getline(SCR *sp, FILE *fp, size_t *lenp)
{
	EX_PRIVATE *exp;
	size_t off;
	int ch;
	char *p;

	exp = EXP(sp);
	for (errno = 0, off = 0, p = exp->ibp;;) {
		if (off >= exp->ibp_len) {
			BINC_RETC(sp, exp->ibp, exp->ibp_len, off + 1);
			p = exp->ibp + off;
		}
		if ((ch = getc(fp)) == EOF && !feof(fp)) {
			if (errno == EINTR) {
				errno = 0;
				clearerr(fp);
				continue;
			}
			return (1);
		}
		if (ch == EOF || ch == '\n') {
			if (ch == EOF && !off)
				return (1);
			*lenp = off;
			return (0);
		}
		*p++ = ch;
		++off;
	}
	/* NOTREACHED */
}