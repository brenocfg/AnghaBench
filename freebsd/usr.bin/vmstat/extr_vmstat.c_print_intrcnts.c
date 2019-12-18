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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;

/* Variables and functions */
 scalar_t__ aflag ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,int,char*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

__attribute__((used)) static void
print_intrcnts(unsigned long *intrcnts, unsigned long *old_intrcnts,
    char *intrnames, unsigned int nintr, size_t istrnamlen, long long period_ms)
{
	unsigned long *intrcnt, *old_intrcnt;
	char *intrname;
	uint64_t inttotal, old_inttotal, total_count, total_rate;
	unsigned long count, rate;
	unsigned int i;

	inttotal = 0;
	old_inttotal = 0;
	intrname = intrnames;
	xo_open_list("interrupt");
	for (i = 0, intrcnt=intrcnts, old_intrcnt=old_intrcnts; i < nintr; i++) {
		if (intrname[0] != '\0' && (*intrcnt != 0 || aflag)) {
			count = *intrcnt - *old_intrcnt;
			rate = ((uint64_t)count * 1000 + period_ms / 2) / period_ms;
			xo_open_instance("interrupt");
			xo_emit("{d:name/%-*s}{ket:name/%s} "
			    "{:total/%20lu} {:rate/%10lu}\n",
			    (int)istrnamlen, intrname, intrname, count, rate);
			xo_close_instance("interrupt");
		}
		intrname += strlen(intrname) + 1;
		inttotal += *intrcnt++;
		old_inttotal += *old_intrcnt++;
	}
	total_count = inttotal - old_inttotal;
	total_rate = (total_count * 1000 + period_ms / 2) / period_ms;
	xo_close_list("interrupt");
	xo_emit("{L:/%-*s} {:total-interrupts/%20ju} "
	    "{:total-rate/%10ju}\n", (int)istrnamlen,
	    "Total", (uintmax_t)total_count, (uintmax_t)total_rate);
}