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
typedef  int /*<<< orphan*/  kaddr ;
typedef  int /*<<< orphan*/  inamlen ;
struct TYPE_2__ {scalar_t__ n_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  X_INTRNAMES ; 
 size_t X_NINTRCNT ; 
 int /*<<< orphan*/  X_SINTRNAMES ; 
 unsigned long* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 long long getuptime () ; 
 int /*<<< orphan*/ * kd ; 
 int /*<<< orphan*/  kread (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  kreadptr (uintptr_t,char*,size_t) ; 
 char* malloc (size_t) ; 
 scalar_t__ mysysctl (char*,char*,size_t*) ; 
 TYPE_1__* namelist ; 
 int /*<<< orphan*/  print_intrcnts (unsigned long*,unsigned long*,char*,unsigned int,size_t,long long) ; 
 unsigned int read_intrcnts (unsigned long**) ; 
 char* reallocf (char*,size_t) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  usleep (unsigned int) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_flush () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 

__attribute__((used)) static void
dointr(unsigned int interval, int reps)
{
	unsigned long *intrcnts, *old_intrcnts;
	char *intrname, *intrnames;
	long long period_ms, old_uptime, uptime;
	size_t clen, inamlen, istrnamlen;
	uintptr_t kaddr;
	unsigned int nintr;

	old_intrcnts = NULL;
	uptime = getuptime();

	/* Get the names of each interrupt source */
	if (kd != NULL) {
		kread(X_SINTRNAMES, &inamlen, sizeof(inamlen));
		if ((intrnames = malloc(inamlen)) == NULL)
			xo_err(1, "malloc()");
		if (namelist[X_NINTRCNT].n_type == 0)
			kread(X_INTRNAMES, intrnames, inamlen);
		else {
			kread(X_INTRNAMES, &kaddr, sizeof(kaddr));
			kreadptr(kaddr, intrnames, inamlen);
		}
	} else {
		for (intrnames = NULL, inamlen = 1024; ; inamlen *= 2) {
			if ((intrnames = reallocf(intrnames, inamlen)) == NULL)
				xo_err(1, "reallocf()");
			if (mysysctl("hw.intrnames", intrnames, &inamlen) == 0)
				break;
		}
	}

	/* Determine the length of the longest interrupt name */
	intrname = intrnames;
	istrnamlen = strlen("interrupt");
	while(*intrname != '\0') {
		clen = strlen(intrname);
		if (clen > istrnamlen)
			istrnamlen = clen;
		intrname += strlen(intrname) + 1;
	}
	xo_emit("{T:/%-*s} {T:/%20s} {T:/%10s}\n",
	    (int)istrnamlen, "interrupt", "total", "rate");

	/* 
	 * Loop reps times printing differential interrupt counts.  If reps is
	 * zero, then run just once, printing total counts
	 */
	xo_open_container("interrupt-statistics");

	period_ms = uptime / 1000000;
	while(1) {
		nintr = read_intrcnts(&intrcnts);
		/* 
		 * Initialize old_intrcnts to 0 for the first pass, so
		 * print_intrcnts will print total interrupts since boot
		 */
		if (old_intrcnts == NULL) {
			old_intrcnts = calloc(nintr, sizeof(unsigned long));
			if (old_intrcnts == NULL)
				xo_err(1, "calloc()");
		}

		print_intrcnts(intrcnts, old_intrcnts, intrnames, nintr,
		    istrnamlen, period_ms);
		xo_flush();

		free(old_intrcnts);
		old_intrcnts = intrcnts;
		if (reps >= 0 && --reps <= 0)
			break;
		usleep(interval * 1000);
		old_uptime = uptime;
		uptime = getuptime();
		period_ms = (uptime - old_uptime) / 1000000;
	}

	xo_close_container("interrupt-statistics");
}