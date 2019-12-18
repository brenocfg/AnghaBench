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
typedef  union dinode {int dummy; } dinode ;
typedef  char* u_long ;
struct inodesc {scalar_t__ id_parent; scalar_t__ id_number; int /*<<< orphan*/  id_func; int /*<<< orphan*/  id_type; int /*<<< orphan*/  id_name; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_2__ {scalar_t__ ino_state; scalar_t__ ino_linkcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR ; 
 int ALTERED ; 
 int BUFSIZ ; 
 int /*<<< orphan*/  DATA ; 
 scalar_t__ DFOUND ; 
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,int) ; 
 int FOUND ; 
 int IFDIR ; 
 int IFMT ; 
 scalar_t__ UFS_ROOTINO ; 
 int /*<<< orphan*/  adjust (struct inodesc*,scalar_t__) ; 
 scalar_t__ allocdir (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int changeino (scalar_t__,char*,scalar_t__) ; 
 int ckinode (union dinode*,struct inodesc*) ; 
 scalar_t__ cursnapshot ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_nlink ; 
 int /*<<< orphan*/  di_size ; 
 int /*<<< orphan*/  findino ; 
 int /*<<< orphan*/  freedir (scalar_t__,scalar_t__) ; 
 union dinode* ginode (scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 TYPE_1__* inoinfo (scalar_t__) ; 
 scalar_t__ lfdir ; 
 int /*<<< orphan*/  lfmode ; 
 char* lfname ; 
 int /*<<< orphan*/  lftempname (char*,scalar_t__) ; 
 scalar_t__ makeentry (scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  memset (struct inodesc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numdirs ; 
 int /*<<< orphan*/  pass4check ; 
 int /*<<< orphan*/  pfatal (char*) ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prtinode (scalar_t__,union dinode*) ; 
 int /*<<< orphan*/  pwarn (char*,...) ; 
 scalar_t__ reply (char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

int
linkup(ino_t orphan, ino_t parentdir, char *name)
{
	union dinode *dp;
	int lostdir;
	ino_t oldlfdir;
	struct inodesc idesc;
	char tempname[BUFSIZ];

	memset(&idesc, 0, sizeof(struct inodesc));
	dp = ginode(orphan);
	lostdir = (DIP(dp, di_mode) & IFMT) == IFDIR;
	pwarn("UNREF %s ", lostdir ? "DIR" : "FILE");
	prtinode(orphan, dp);
	printf("\n");
	if (preen && DIP(dp, di_size) == 0)
		return (0);
	if (cursnapshot != 0) {
		pfatal("FILE LINKUP IN SNAPSHOT");
		return (0);
	}
	if (preen)
		printf(" (RECONNECTED)\n");
	else
		if (reply("RECONNECT") == 0)
			return (0);
	if (lfdir == 0) {
		dp = ginode(UFS_ROOTINO);
		idesc.id_name = strdup(lfname);
		idesc.id_type = DATA;
		idesc.id_func = findino;
		idesc.id_number = UFS_ROOTINO;
		if ((ckinode(dp, &idesc) & FOUND) != 0) {
			lfdir = idesc.id_parent;
		} else {
			pwarn("NO lost+found DIRECTORY");
			if (preen || reply("CREATE")) {
				lfdir = allocdir(UFS_ROOTINO, (ino_t)0, lfmode);
				if (lfdir != 0) {
					if (makeentry(UFS_ROOTINO, lfdir,
					    lfname) != 0) {
						numdirs++;
						if (preen)
							printf(" (CREATED)\n");
					} else {
						freedir(lfdir, UFS_ROOTINO);
						lfdir = 0;
						if (preen)
							printf("\n");
					}
				}
			}
		}
		if (lfdir == 0) {
			pfatal("SORRY. CANNOT CREATE lost+found DIRECTORY");
			printf("\n\n");
			return (0);
		}
	}
	dp = ginode(lfdir);
	if ((DIP(dp, di_mode) & IFMT) != IFDIR) {
		pfatal("lost+found IS NOT A DIRECTORY");
		if (reply("REALLOCATE") == 0)
			return (0);
		oldlfdir = lfdir;
		if ((lfdir = allocdir(UFS_ROOTINO, (ino_t)0, lfmode)) == 0) {
			pfatal("SORRY. CANNOT CREATE lost+found DIRECTORY\n\n");
			return (0);
		}
		if ((changeino(UFS_ROOTINO, lfname, lfdir) & ALTERED) == 0) {
			pfatal("SORRY. CANNOT CREATE lost+found DIRECTORY\n\n");
			return (0);
		}
		inodirty(dp);
		idesc.id_type = ADDR;
		idesc.id_func = pass4check;
		idesc.id_number = oldlfdir;
		adjust(&idesc, inoinfo(oldlfdir)->ino_linkcnt + 1);
		inoinfo(oldlfdir)->ino_linkcnt = 0;
		dp = ginode(lfdir);
	}
	if (inoinfo(lfdir)->ino_state != DFOUND) {
		pfatal("SORRY. NO lost+found DIRECTORY\n\n");
		return (0);
	}
	(void)lftempname(tempname, orphan);
	if (makeentry(lfdir, orphan, (name ? name : tempname)) == 0) {
		pfatal("SORRY. NO SPACE IN lost+found DIRECTORY");
		printf("\n\n");
		return (0);
	}
	inoinfo(orphan)->ino_linkcnt--;
	if (lostdir) {
		if ((changeino(orphan, "..", lfdir) & ALTERED) == 0 &&
		    parentdir != (ino_t)-1)
			(void)makeentry(orphan, lfdir, "..");
		dp = ginode(lfdir);
		DIP_SET(dp, di_nlink, DIP(dp, di_nlink) + 1);
		inodirty(dp);
		inoinfo(lfdir)->ino_linkcnt++;
		pwarn("DIR I=%lu CONNECTED. ", (u_long)orphan);
		if (parentdir != (ino_t)-1) {
			printf("PARENT WAS I=%lu\n", (u_long)parentdir);
			/*
			 * The parent directory, because of the ordering
			 * guarantees, has had the link count incremented
			 * for the child, but no entry was made.  This
			 * fixes the parent link count so that fsck does
			 * not need to be rerun.
			 */
			inoinfo(parentdir)->ino_linkcnt++;
		}
		if (preen == 0)
			printf("\n");
	}
	return (1);
}