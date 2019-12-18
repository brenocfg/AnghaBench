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
struct inodesc {scalar_t__ id_parent; scalar_t__ id_number; char* id_name; int /*<<< orphan*/  id_func; int /*<<< orphan*/  id_fix; int /*<<< orphan*/  id_type; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int FOUND ; 
 int /*<<< orphan*/  IGNORE ; 
 int /*<<< orphan*/  INO_IS_DVALID (scalar_t__) ; 
 int MAXPATHLEN ; 
 size_t UFS_MAXNAMLEN ; 
 scalar_t__ UFS_ROOTINO ; 
 int ckinode (int /*<<< orphan*/ ,struct inodesc*) ; 
 int /*<<< orphan*/  findino ; 
 int /*<<< orphan*/  findname ; 
 int /*<<< orphan*/  ginode (scalar_t__) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (struct inodesc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

void
getpathname(char *namebuf, ino_t curdir, ino_t ino)
{
	int len;
	char *cp;
	struct inodesc idesc;
	static int busy = 0;

	if (curdir == ino && ino == UFS_ROOTINO) {
		(void)strcpy(namebuf, "/");
		return;
	}
	if (busy || !INO_IS_DVALID(curdir)) {
		(void)strcpy(namebuf, "?");
		return;
	}
	busy = 1;
	memset(&idesc, 0, sizeof(struct inodesc));
	idesc.id_type = DATA;
	idesc.id_fix = IGNORE;
	cp = &namebuf[MAXPATHLEN - 1];
	*cp = '\0';
	if (curdir != ino) {
		idesc.id_parent = curdir;
		goto namelookup;
	}
	while (ino != UFS_ROOTINO) {
		idesc.id_number = ino;
		idesc.id_func = findino;
		idesc.id_name = strdup("..");
		if ((ckinode(ginode(ino), &idesc) & FOUND) == 0)
			break;
	namelookup:
		idesc.id_number = idesc.id_parent;
		idesc.id_parent = ino;
		idesc.id_func = findname;
		idesc.id_name = namebuf;
		if ((ckinode(ginode(idesc.id_number), &idesc)&FOUND) == 0)
			break;
		len = strlen(namebuf);
		cp -= len;
		memmove(cp, namebuf, (size_t)len);
		*--cp = '/';
		if (cp < &namebuf[UFS_MAXNAMLEN])
			break;
		ino = idesc.id_number;
	}
	busy = 0;
	if (ino != UFS_ROOTINO)
		*--cp = '?';
	memmove(namebuf, cp, (size_t)(&namebuf[MAXPATHLEN] - cp));
}