#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct inodesc {int id_number; int /*<<< orphan*/  id_func; int /*<<< orphan*/  id_type; } ;
typedef  int ino_t ;
struct TYPE_6__ {int ino_state; int ino_linkcnt; } ;
struct TYPE_5__ {int il_numalloced; } ;
struct TYPE_4__ {int fs_ncg; int fs_ipg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR ; 
#define  DCLEAR 135 
#define  DFOUND 134 
 int /*<<< orphan*/  DIP (union dinode*,int /*<<< orphan*/ ) ; 
#define  DSTATE 133 
#define  DZLINK 132 
 int /*<<< orphan*/  EEXIT ; 
#define  FCLEAR 131 
#define  FSTATE 130 
#define  FZLINK 129 
 int UFS_ROOTINO ; 
#define  USTATE 128 
 int /*<<< orphan*/  adjust (struct inodesc*,short) ; 
 char* cdevname ; 
 int /*<<< orphan*/  clri (struct inodesc*,char*,int) ; 
 int /*<<< orphan*/  cursnapshot ; 
 int /*<<< orphan*/  di_size ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 union dinode* ginode (int) ; 
 scalar_t__ got_sigalarm ; 
 scalar_t__ got_siginfo ; 
 TYPE_3__* inoinfo (int) ; 
 TYPE_2__* inostathead ; 
 int /*<<< orphan*/  memset (struct inodesc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pass4check ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 TYPE_1__ sblock ; 
 int /*<<< orphan*/  setproctitle (char*,char*,int) ; 

void
pass4(void)
{
	ino_t inumber;
	union dinode *dp;
	struct inodesc idesc;
	int i, n, cg;

	memset(&idesc, 0, sizeof(struct inodesc));
	idesc.id_type = ADDR;
	idesc.id_func = pass4check;
	for (cg = 0; cg < sblock.fs_ncg; cg++) {
		if (got_siginfo) {
			printf("%s: phase 4: cyl group %d of %d (%d%%)\n",
			    cdevname, cg, sblock.fs_ncg,
			    cg * 100 / sblock.fs_ncg);
			got_siginfo = 0;
		}
		if (got_sigalarm) {
			setproctitle("%s p4 %d%%", cdevname,
			    cg * 100 / sblock.fs_ncg);
			got_sigalarm = 0;
		}
		inumber = cg * sblock.fs_ipg;
		for (i = 0; i < inostathead[cg].il_numalloced; i++, inumber++) {
			if (inumber < UFS_ROOTINO)
				continue;
			idesc.id_number = inumber;
			switch (inoinfo(inumber)->ino_state) {

			case FZLINK:
			case DZLINK:
				if (inoinfo(inumber)->ino_linkcnt == 0) {
					clri(&idesc, "UNREF", 1);
					break;
				}
				/* fall through */

			case FSTATE:
			case DFOUND:
				n = inoinfo(inumber)->ino_linkcnt;
				if (n) {
					adjust(&idesc, (short)n);
					break;
				}
				break;

			case DSTATE:
				clri(&idesc, "UNREF", 1);
				break;

			case DCLEAR:
				/* if on snapshot, already cleared */
				if (cursnapshot != 0)
					break;
				dp = ginode(inumber);
				if (DIP(dp, di_size) == 0) {
					clri(&idesc, "ZERO LENGTH", 1);
					break;
				}
				/* fall through */
			case FCLEAR:
				clri(&idesc, "BAD/DUP", 1);
				break;

			case USTATE:
				break;

			default:
				errx(EEXIT, "BAD STATE %d FOR INODE I=%ju",
				    inoinfo(inumber)->ino_state,
				    (uintmax_t)inumber);
			}
		}
	}
}