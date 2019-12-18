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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ dqb_btime; scalar_t__ dqb_itime; scalar_t__ dqb_curinodes; scalar_t__ dqb_isoftlimit; scalar_t__ dqb_ihardlimit; scalar_t__ dqb_curblocks; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_bhardlimit; } ;
struct quotause {TYPE_1__ dqblk; int /*<<< orphan*/  fsname; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int USRQUOTA ; 
 char* ctime (scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
showrawquotas(int type, u_long id, struct quotause *qup)
{
	time_t t;

	printf("Raw %s quota information for id %lu on %s\n",
	    type == USRQUOTA ? "user" : "group", id, qup->fsname);
	printf("block hard limit:     %ju\n",
	    (uintmax_t)qup->dqblk.dqb_bhardlimit);
	printf("block soft limit:     %ju\n",
	    (uintmax_t)qup->dqblk.dqb_bsoftlimit);
	printf("current block count:  %ju\n",
	    (uintmax_t)qup->dqblk.dqb_curblocks);
	printf("i-node hard limit:    %ju\n",
	    (uintmax_t)qup->dqblk.dqb_ihardlimit);
	printf("i-node soft limit:    %ju\n",
	    (uintmax_t)qup->dqblk.dqb_isoftlimit);
	printf("current i-node count: %ju\n",
	    (uintmax_t)qup->dqblk.dqb_curinodes);
	printf("block grace time:     %jd",
	    (intmax_t)qup->dqblk.dqb_btime);
	if (qup->dqblk.dqb_btime != 0) {
		t = qup->dqblk.dqb_btime;
		printf(" %s", ctime(&t));
	} else {
		printf("\n");
	}
	printf("i-node grace time:    %jd", (intmax_t)qup->dqblk.dqb_itime);
	if (qup->dqblk.dqb_itime != 0) {
		t = qup->dqblk.dqb_itime;
		printf(" %s", ctime(&t));
	} else {
		printf("\n");
	}
}