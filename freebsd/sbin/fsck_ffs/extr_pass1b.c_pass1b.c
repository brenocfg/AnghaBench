#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
struct inodesc {scalar_t__ id_number; int /*<<< orphan*/  id_func; int /*<<< orphan*/  id_type; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_4__ {scalar_t__ ino_state; } ;
struct TYPE_3__ {int fs_ncg; int fs_ipg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR ; 
 int STOP ; 
 scalar_t__ UFS_ROOTINO ; 
 scalar_t__ USTATE ; 
 char* cdevname ; 
 int ckinode (union dinode*,struct inodesc*) ; 
 int /*<<< orphan*/  duphead ; 
 int /*<<< orphan*/  duplist ; 
 union dinode* ginode (scalar_t__) ; 
 scalar_t__ got_sigalarm ; 
 scalar_t__ got_siginfo ; 
 TYPE_2__* inoinfo (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct inodesc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pass1bcheck ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 int rerun ; 
 TYPE_1__ sblock ; 
 int /*<<< orphan*/  setproctitle (char*,char*,int) ; 

void
pass1b(void)
{
	int c, i;
	union dinode *dp;
	struct inodesc idesc;
	ino_t inumber;

	memset(&idesc, 0, sizeof(struct inodesc));
	idesc.id_type = ADDR;
	idesc.id_func = pass1bcheck;
	duphead = duplist;
	inumber = 0;
	for (c = 0; c < sblock.fs_ncg; c++) {
		if (got_siginfo) {
			printf("%s: phase 1b: cyl group %d of %d (%d%%)\n",
			    cdevname, c, sblock.fs_ncg,
			    c * 100 / sblock.fs_ncg);
			got_siginfo = 0;
		}
		if (got_sigalarm) {
			setproctitle("%s p1b %d%%", cdevname,
			    c * 100 / sblock.fs_ncg);
			got_sigalarm = 0;
		}
		for (i = 0; i < sblock.fs_ipg; i++, inumber++) {
			if (inumber < UFS_ROOTINO)
				continue;
			dp = ginode(inumber);
			if (dp == NULL)
				continue;
			idesc.id_number = inumber;
			if (inoinfo(inumber)->ino_state != USTATE &&
			    (ckinode(dp, &idesc) & STOP)) {
				rerun = 1;
				return;
			}
		}
	}
}