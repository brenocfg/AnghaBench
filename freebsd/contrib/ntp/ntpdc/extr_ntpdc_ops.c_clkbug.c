#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int32 ;
struct parse {TYPE_1__* argval; int /*<<< orphan*/  nargs; } ;
struct info_clkbug {int /*<<< orphan*/ * times; int /*<<< orphan*/  stimes; scalar_t__ ntimes; int /*<<< orphan*/ * values; int /*<<< orphan*/  svalues; scalar_t__ nvalues; int /*<<< orphan*/  clockadr; } ;
typedef  int /*<<< orphan*/  l_fp ;
struct TYPE_2__ {int /*<<< orphan*/  netnum; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int COUNTOF (int /*<<< orphan*/ *) ; 
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 int INFO_ERR_IMPL ; 
 int /*<<< orphan*/  MAXARGS ; 
 int /*<<< orphan*/  NSRCADR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NTOHL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NUMCBUGTIMES ; 
 int NUMCBUGVALUES ; 
 int /*<<< orphan*/  REQ_GET_CLKBUGINFO ; 
 int /*<<< orphan*/  checkitems (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkitemsize (size_t,int) ; 
 int doquery (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,char*,size_t*,size_t*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ impl_ver ; 
 char* lfptoa (int /*<<< orphan*/ *,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 char* numtoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 char* uglydate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clkbug(
	struct parse *pcmd,
	FILE *fp
	)
{
	register int i;
	register int n;
	register u_int32 s;
	struct info_clkbug *cl;
	/* 8 is the maximum number of clocks which will fit in a packet */
	u_long clist[min(MAXARGS, 8)];
	u_int32 ltemp;
	size_t qitemlim;
	size_t qitems;
	size_t items;
	size_t itemsize;
	int res;
	int needsp;
	l_fp ts;

	qitemlim = min(pcmd->nargs, COUNTOF(clist));
	for (qitems = 0; qitems < qitemlim; qitems++)
		clist[qitems] = NSRCADR(&pcmd->argval[qitems].netnum);

again:
	res = doquery(impl_ver, REQ_GET_CLKBUGINFO, 0, qitems,
		      sizeof(u_int32), (char *)clist, &items,
		      &itemsize, (void *)&cl, 0, sizeof(struct info_clkbug));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res != 0)
		return;

	if (!checkitems(items, fp))
		return;

	if (!checkitemsize(itemsize, sizeof(struct info_clkbug)))
		return;

	while (items-- > 0) {
		(void) fprintf(fp, "clock address:        %s\n",
			       numtoa(cl->clockadr));
		n = (int)cl->nvalues;
		(void) fprintf(fp, "values: %d", n);
		s = ntohs(cl->svalues);
		if (n > NUMCBUGVALUES)
		    n = NUMCBUGVALUES;
		for (i = 0; i < n; i++) {
			ltemp = ntohl(cl->values[i]);
			ltemp &= 0xffffffff;	/* HMS: This does nothing now */
			if ((i & 0x3) == 0)
			    (void) fprintf(fp, "\n");
			if (s & (1 << i))
			    (void) fprintf(fp, "%12ld", (u_long)ltemp);
			else
			    (void) fprintf(fp, "%12lu", (u_long)ltemp);
		}
		(void) fprintf(fp, "\n");

		n = (int)cl->ntimes;
		(void) fprintf(fp, "times: %d", n);
		s = ntohl(cl->stimes);
		if (n > NUMCBUGTIMES)
		    n = NUMCBUGTIMES;
		needsp = 0;
		for (i = 0; i < n; i++) {
			if ((i & 0x1) == 0) {
			    (void) fprintf(fp, "\n");
			} else {
				for (;needsp > 0; needsp--)
				    putc(' ', fp);
			}
			NTOHL_FP(&cl->times[i], &ts);
			if (s & (1 << i)) {
				(void) fprintf(fp, "%17s",
					       lfptoa(&ts, 6));
				needsp = 22;
			} else {
				(void) fprintf(fp, "%37s",
					       uglydate(&ts));
				needsp = 2;
			}
		}
		(void) fprintf(fp, "\n");
		if (items > 0) {
			cl++;
			(void) fprintf(fp, "\n");
		}
	}
}