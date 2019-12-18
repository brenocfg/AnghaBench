#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
struct inodesc {scalar_t__ id_number; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_3__ {scalar_t__ value; int size; } ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,int) ; 
 int IFDIR ; 
 int IFMT ; 
 int /*<<< orphan*/  MIBSIZE ; 
 int /*<<< orphan*/  adjrefcnt ; 
 scalar_t__ bkgrdflag ; 
 int /*<<< orphan*/  clri (struct inodesc*,char*,int) ; 
 TYPE_1__ cmd ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_nlink ; 
 union dinode* ginode (scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 scalar_t__ lfdir ; 
 char* lfname ; 
 scalar_t__ linkup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfatal (char*) ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prtinode (scalar_t__,union dinode*) ; 
 int /*<<< orphan*/  pwarn (char*,char*) ; 
 int reply (char*) ; 
 int resolved ; 
 int /*<<< orphan*/  rwerror (char*,scalar_t__) ; 
 int sysctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ usedsoftdep ; 

void
adjust(struct inodesc *idesc, int lcnt)
{
	union dinode *dp;
	int saveresolved;

	dp = ginode(idesc->id_number);
	if (DIP(dp, di_nlink) == lcnt) {
		/*
		 * If we have not hit any unresolved problems, are running
		 * in preen mode, and are on a file system using soft updates,
		 * then just toss any partially allocated files.
		 */
		if (resolved && (preen || bkgrdflag) && usedsoftdep) {
			clri(idesc, "UNREF", 1);
			return;
		} else {
			/*
			 * The file system can be marked clean even if
			 * a file is not linked up, but is cleared.
			 * Hence, resolved should not be cleared when
			 * linkup is answered no, but clri is answered yes.
			 */
			saveresolved = resolved;
			if (linkup(idesc->id_number, (ino_t)0, NULL) == 0) {
				resolved = saveresolved;
				clri(idesc, "UNREF", 0);
				return;
			}
			/*
			 * Account for the new reference created by linkup().
			 */
			dp = ginode(idesc->id_number);
			lcnt--;
		}
	}
	if (lcnt != 0) {
		pwarn("LINK COUNT %s", (lfdir == idesc->id_number) ? lfname :
			((DIP(dp, di_mode) & IFMT) == IFDIR ? "DIR" : "FILE"));
		prtinode(idesc->id_number, dp);
		printf(" COUNT %d SHOULD BE %d",
			DIP(dp, di_nlink), DIP(dp, di_nlink) - lcnt);
		if (preen || usedsoftdep) {
			if (lcnt < 0) {
				printf("\n");
				pfatal("LINK COUNT INCREASING");
			}
			if (preen)
				printf(" (ADJUSTED)\n");
		}
		if (preen || reply("ADJUST") == 1) {
			if (bkgrdflag == 0) {
				DIP_SET(dp, di_nlink, DIP(dp, di_nlink) - lcnt);
				inodirty(dp);
			} else {
				cmd.value = idesc->id_number;
				cmd.size = -lcnt;
				if (debug)
					printf("adjrefcnt ino %ld amt %lld\n",
					    (long)cmd.value,
					    (long long)cmd.size);
				if (sysctl(adjrefcnt, MIBSIZE, 0, 0,
				    &cmd, sizeof cmd) == -1)
					rwerror("ADJUST INODE", cmd.value);
			}
		}
	}
}