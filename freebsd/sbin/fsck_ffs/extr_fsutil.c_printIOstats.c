#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_7__ {int tv_sec; int tv_nsec; } ;
struct TYPE_6__ {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int BT_NUMBUFTYPES ; 
 int /*<<< orphan*/  CLOCK_REALTIME_PRECISE ; 
 char** buftype ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int diskreads ; 
 TYPE_1__ finishpass ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* readcnt ; 
 TYPE_3__* readtime ; 
 int /*<<< orphan*/  startpass ; 
 int /*<<< orphan*/  timespecsub (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void printIOstats(void)
{
	long long msec, totalmsec;
	int i;

	clock_gettime(CLOCK_REALTIME_PRECISE, &finishpass);
	timespecsub(&finishpass, &startpass, &finishpass);
	printf("Running time: %jd.%03ld sec\n",
		(intmax_t)finishpass.tv_sec, finishpass.tv_nsec / 1000000);
	printf("buffer reads by type:\n");
	for (totalmsec = 0, i = 0; i < BT_NUMBUFTYPES; i++)
		totalmsec += readtime[i].tv_sec * 1000 +
		    readtime[i].tv_nsec / 1000000;
	if (totalmsec == 0)
		totalmsec = 1;
	for (i = 0; i < BT_NUMBUFTYPES; i++) {
		if (readcnt[i] == 0)
			continue;
		msec =
		    readtime[i].tv_sec * 1000 + readtime[i].tv_nsec / 1000000;
		printf("%21s:%8ld %2ld.%ld%% %4jd.%03ld sec %2lld.%lld%%\n",
		    buftype[i], readcnt[i], readcnt[i] * 100 / diskreads,
		    (readcnt[i] * 1000 / diskreads) % 10,
		    (intmax_t)readtime[i].tv_sec, readtime[i].tv_nsec / 1000000,
		    msec * 100 / totalmsec, (msec * 1000 / totalmsec) % 10);
	}
	printf("\n");
}