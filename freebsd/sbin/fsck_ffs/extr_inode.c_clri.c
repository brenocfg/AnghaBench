#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
struct inodesc {scalar_t__ id_number; } ;
struct TYPE_5__ {int /*<<< orphan*/  ino_state; } ;
struct TYPE_4__ {int size; scalar_t__ value; } ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int IFDIR ; 
 int IFMT ; 
 int /*<<< orphan*/  MIBSIZE ; 
 int /*<<< orphan*/  USTATE ; 
 int /*<<< orphan*/  adjrefcnt ; 
 scalar_t__ bkgrdflag ; 
 int /*<<< orphan*/  ckinode (union dinode*,struct inodesc*) ; 
 int /*<<< orphan*/  clearinode (union dinode*) ; 
 TYPE_1__ cmd ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_nlink ; 
 union dinode* ginode (scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 TYPE_2__* inoinfo (scalar_t__) ; 
 int /*<<< orphan*/  n_files ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prtinode (scalar_t__,union dinode*) ; 
 int /*<<< orphan*/  pwarn (char*,char const*,char*) ; 
 int reply (char*) ; 
 int /*<<< orphan*/  rwerror (char*,scalar_t__) ; 
 int sysctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void
clri(struct inodesc *idesc, const char *type, int flag)
{
	union dinode *dp;

	dp = ginode(idesc->id_number);
	if (flag == 1) {
		pwarn("%s %s", type,
		    (DIP(dp, di_mode) & IFMT) == IFDIR ? "DIR" : "FILE");
		prtinode(idesc->id_number, dp);
		printf("\n");
	}
	if (preen || reply("CLEAR") == 1) {
		if (preen)
			printf(" (CLEARED)\n");
		n_files--;
		if (bkgrdflag == 0) {
			(void)ckinode(dp, idesc);
			inoinfo(idesc->id_number)->ino_state = USTATE;
			clearinode(dp);
			inodirty(dp);
		} else {
			cmd.value = idesc->id_number;
			cmd.size = -DIP(dp, di_nlink);
			if (debug)
				printf("adjrefcnt ino %ld amt %lld\n",
				    (long)cmd.value, (long long)cmd.size);
			if (sysctl(adjrefcnt, MIBSIZE, 0, 0,
			    &cmd, sizeof cmd) == -1)
				rwerror("ADJUST INODE", cmd.value);
		}
	}
}