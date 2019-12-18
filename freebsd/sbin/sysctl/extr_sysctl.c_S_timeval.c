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
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_sec; int /*<<< orphan*/  tv_usec; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctime (scalar_t__*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,size_t,int) ; 

__attribute__((used)) static int
S_timeval(size_t l2, void *p)
{
	struct timeval *tv = (struct timeval*)p;
	time_t tv_sec;
	char *p1, *p2;

	if (l2 != sizeof(*tv)) {
		warnx("S_timeval %zu != %zu", l2, sizeof(*tv));
		return (1);
	}
	printf(hflag ? "{ sec = %'jd, usec = %'ld } " :
		"{ sec = %jd, usec = %ld } ",
		(intmax_t)tv->tv_sec, tv->tv_usec);
	tv_sec = tv->tv_sec;
	p1 = strdup(ctime(&tv_sec));
	for (p2=p1; *p2 ; p2++)
		if (*p2 == '\n')
			*p2 = '\0';
	fputs(p1, stdout);
	free(p1);
	return (0);
}