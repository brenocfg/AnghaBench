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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inoinfo {intptr_t i_dotdot; intptr_t i_parent; intptr_t i_number; } ;
struct inodesc {intptr_t id_number; intptr_t id_parent; int /*<<< orphan*/  id_func; void* id_type; TYPE_1__* id_dirp; int /*<<< orphan*/  id_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  ino_linkcnt; } ;
struct TYPE_6__ {intptr_t value; intptr_t size; } ;
struct TYPE_5__ {intptr_t d_ino; char* d_name; } ;

/* Variables and functions */
 void* DATA ; 
 int FOUND ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int ckinode (int /*<<< orphan*/ ,struct inodesc*) ; 
 TYPE_2__ cmd ; 
 scalar_t__ cursnapshot ; 
 int /*<<< orphan*/  deleteentry ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  findino ; 
 int /*<<< orphan*/  getpathname (char*,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  ginode (intptr_t) ; 
 TYPE_3__* inoinfo (intptr_t) ; 
 int /*<<< orphan*/  memset (struct inodesc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pwarn (char*,char*,char*) ; 
 int reply (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static int
fix_extraneous(struct inoinfo *inp, struct inodesc *idesc)
{
	char *cp;
	struct inodesc dotdesc;
	char oldname[MAXPATHLEN + 1];
	char newname[MAXPATHLEN + 1];

	/*
	 * If we have not yet found "..", look it up now so we know
	 * which inode the directory itself believes is its parent.
	 */
	if (inp->i_dotdot == 0) {
		memset(&dotdesc, 0, sizeof(struct inodesc));
		dotdesc.id_type = DATA;
		dotdesc.id_number = idesc->id_dirp->d_ino;
		dotdesc.id_func = findino;
		dotdesc.id_name = strdup("..");
		if ((ckinode(ginode(dotdesc.id_number), &dotdesc) & FOUND))
			inp->i_dotdot = dotdesc.id_parent;
	}
	/*
	 * We have the previously found old name (inp->i_parent) and the
	 * just found new name (idesc->id_number). We have five cases:
	 * 1)  ".." is missing - can remove either name, choose to delete
	 *     new one and let fsck create ".." pointing to old name.
	 * 2) Both new and old are in same directory, choose to delete
	 *    the new name and let fsck fix ".." if it is wrong.
	 * 3) ".." does not point to the new name, so delete it and let
	 *    fsck fix ".." to point to the old one if it is wrong.
	 * 4) ".." points to the old name only, so delete the new one.
	 * 5) ".." points to the new name only, so delete the old one.
	 *
	 * For cases 1-4 we eliminate the new name;
	 * for case 5 we eliminate the old name.
	 */
	if (inp->i_dotdot == 0 ||		    /* Case 1 */
	    idesc->id_number == inp->i_parent ||    /* Case 2 */
	    inp->i_dotdot != idesc->id_number ||    /* Case 3 */
	    inp->i_dotdot == inp->i_parent) {	    /* Case 4 */
		getpathname(newname, idesc->id_number, idesc->id_number);
		if (strcmp(newname, "/") != 0)
			strcat (newname, "/");
		strcat(newname, idesc->id_dirp->d_name);
		getpathname(oldname, inp->i_number, inp->i_number);
		pwarn("%s IS AN EXTRANEOUS HARD LINK TO DIRECTORY %s",
		    newname, oldname);
		if (cursnapshot != 0) {
			/*
			 * We need to
			 *    setcwd(idesc->id_number);
			 *    unlink(idesc->id_dirp->d_name);
			 */
			cmd.value = idesc->id_number;
			if (sysctlbyname("vfs.ffs.setcwd", 0, 0,
			    &cmd, sizeof cmd) == -1) {
				printf(" (IGNORED)\n");
				return (0);
			}
			cmd.value = (intptr_t)idesc->id_dirp->d_name;
			cmd.size = inp->i_number; /* verify same name */
			if (sysctlbyname("vfs.ffs.unlink", 0, 0,
			    &cmd, sizeof cmd) == -1) {
				printf(" (UNLINK FAILED: %s)\n",
				    strerror(errno));
				return (0);
			}
			printf(" (REMOVED)\n");
			return (0);
		}
		if (preen) {
			printf(" (REMOVED)\n");
			return (1);
		}
		return (reply("REMOVE"));
	}
	/*
	 * None of the first four cases above, so must be case (5).
	 * Eliminate the old name and make the new the name the parent.
	 */
	getpathname(oldname, inp->i_parent, inp->i_number);
	getpathname(newname, inp->i_number, inp->i_number);
	pwarn("%s IS AN EXTRANEOUS HARD LINK TO DIRECTORY %s", oldname,
	    newname);
	if (cursnapshot != 0) {
		/*
		 * We need to
		 *    setcwd(inp->i_parent);
		 *    unlink(last component of oldname pathname);
		 */
		cmd.value = inp->i_parent;
		if (sysctlbyname("vfs.ffs.setcwd", 0, 0,
		    &cmd, sizeof cmd) == -1) {
			printf(" (IGNORED)\n");
			return (0);
		}
		if ((cp = strchr(oldname, '/')) == NULL) {
			printf(" (IGNORED)\n");
			return (0);
		}
		cmd.value = (intptr_t)(cp + 1);
		cmd.size = inp->i_number; /* verify same name */
		if (sysctlbyname("vfs.ffs.unlink", 0, 0,
		    &cmd, sizeof cmd) == -1) {
			printf(" (UNLINK FAILED: %s)\n",
			    strerror(errno));
			return (0);
		}
		printf(" (REMOVED)\n");
		inp->i_parent = idesc->id_number;  /* reparent to correct dir */
		return (0);
	}
	if (!preen && !reply("REMOVE"))
		return (0);
	memset(&dotdesc, 0, sizeof(struct inodesc));
	dotdesc.id_type = DATA;
	dotdesc.id_number = inp->i_parent; /* directory in which name appears */
	dotdesc.id_parent = inp->i_number; /* inode number in entry to delete */
	dotdesc.id_func = deleteentry;
	if ((ckinode(ginode(dotdesc.id_number), &dotdesc) & FOUND) && preen)
		printf(" (REMOVED)\n");
	inp->i_parent = idesc->id_number;  /* reparent to correct directory */
	inoinfo(inp->i_number)->ino_linkcnt++; /* name gone, return reference */
	return (0);
}