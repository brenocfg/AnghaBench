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
typedef  int u_char ;
struct timezone {int dummy; } ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ dofilter ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,struct timezone*) ; 
 struct timeval lasttv ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 char* progname ; 
 int /*<<< orphan*/  raw_filter (unsigned int,struct timeval*) ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  stderr ; 

int
process_raw(
	int s
	)
{
	u_char c;
	int n;
	struct timeval tv;
	struct timeval difftv;

	while ((n = read(s, &c, sizeof(char))) > 0) {
		(void) gettimeofday(&tv, (struct timezone *)0);
		if (dofilter)
		    raw_filter((unsigned int)c, &tv);
		else {
			difftv.tv_sec = tv.tv_sec - lasttv.tv_sec;
			difftv.tv_usec = tv.tv_usec - lasttv.tv_usec;
			if (difftv.tv_usec < 0) {
				difftv.tv_sec--;
				difftv.tv_usec += 1000000;
			}
			(void) printf("%02x\t%lu.%06lu\t%lu.%06lu\n",
				      c, tv.tv_sec, tv.tv_usec, difftv.tv_sec,
				      difftv.tv_usec);
			lasttv = tv;
		}
	}

	if (n == 0) {
		(void) fprintf(stderr, "%s: zero returned on read\n", progname);
		exit(1);
	} else
	    error("read()", "", "");
}