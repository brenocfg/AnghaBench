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

/* Variables and functions */
 scalar_t__ EOF ; 
 scalar_t__ dspace ; 
 scalar_t__ fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 char ochar ; 
 int ogap ; 
 int /*<<< orphan*/  pfail () ; 
 scalar_t__ putchar (char) ; 
 int /*<<< orphan*/  stdout ; 

int
otln(char *buf, int cnt, int *svips, int *svops, int mor)
{
	int ops;		/* last col output */
	int ips;		/* last col in buf examined */
	int gap = ogap;
	int tbps;
	char *endbuf;

	if (ogap) {
		/*
		 * contracting on output
		 */
		endbuf = buf + cnt;
		ops = *svops;
		ips = *svips;
		while (buf < endbuf) {
			/*
			 * count number of spaces and ochar in buffer
			 */
			if (*buf == ' ') {
				++ips;
				++buf;
				continue;
			}

			/*
			 * simulate ochar processing
			 */
			if (*buf == ochar) {
				ips += gap - (ips % gap);
				++buf;
				continue;
			}

			/*
			 * got a non space char; contract out spaces
			 */
			while (ips - ops > 1) {
				/*
				 * use as many ochar as will fit
				 */
				if ((tbps = ops + gap - (ops % gap)) > ips)
					break;
				if (putchar(ochar) == EOF) {
					pfail();
					return(1);
				}
				ops = tbps;
			}

			while (ops < ips) {
				/*
				 * finish off with spaces
				 */
				if (putchar(' ') == EOF) {
					pfail();
					return(1);
				}
				++ops;
			}

			/*
			 * output non space char
			 */
			if (putchar(*buf++) == EOF) {
				pfail();
				return(1);
			}
			++ips;
			++ops;
		}

		if (mor > 0) {
			/*
			 * if incomplete line, save position counts
			 */
			*svops = ops;
			*svips = ips;
			return(0);
		}

		if (mor < 0) {
			while (ips - ops > 1) {
				/*
				 * use as many ochar as will fit
				 */
				if ((tbps = ops + gap - (ops % gap)) > ips)
					break;
				if (putchar(ochar) == EOF) {
					pfail();
					return(1);
				}
				ops = tbps;
			}
			while (ops < ips) {
				/*
				 * finish off with spaces
				 */
				if (putchar(' ') == EOF) {
					pfail();
					return(1);
				}
				++ops;
			}
			return(0);
		}
	} else {
		/*
		 * output is not contracted
		 */
		if (cnt && (fwrite(buf, sizeof(char), cnt, stdout) <= 0)) {
			pfail();
			return(1);
		}
		if (mor != 0)
			return(0);
	}

	/*
	 * process line end and double space as required
	 */
	if ((putchar('\n') == EOF) || (dspace && (putchar('\n') == EOF))) {
		pfail();
		return(1);
	}
	return(0);
}