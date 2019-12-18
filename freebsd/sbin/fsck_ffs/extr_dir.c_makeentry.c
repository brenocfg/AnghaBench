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
typedef  union dinode {int dummy; } dinode ;
struct inodesc {int /*<<< orphan*/  id_name; int /*<<< orphan*/  id_fix; scalar_t__ id_parent; scalar_t__ id_number; int /*<<< orphan*/  id_func; int /*<<< orphan*/  id_type; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int ALTERED ; 
 int /*<<< orphan*/  DATA ; 
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DIRBLKSIZ ; 
 int /*<<< orphan*/  DONTKNOW ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 scalar_t__ UFS_ROOTINO ; 
 int ckinode (union dinode*,struct inodesc*) ; 
 int /*<<< orphan*/  di_size ; 
 scalar_t__ expanddir (union dinode*,char*) ; 
 int /*<<< orphan*/  getpathname (char*,scalar_t__,scalar_t__) ; 
 union dinode* ginode (scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 scalar_t__ maxino ; 
 int /*<<< orphan*/  memset (struct inodesc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mkentry ; 
 int /*<<< orphan*/  roundup (int,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

int
makeentry(ino_t parent, ino_t ino, const char *name)
{
	union dinode *dp;
	struct inodesc idesc;
	char pathbuf[MAXPATHLEN + 1];

	if (parent < UFS_ROOTINO || parent >= maxino ||
	    ino < UFS_ROOTINO || ino >= maxino)
		return (0);
	memset(&idesc, 0, sizeof(struct inodesc));
	idesc.id_type = DATA;
	idesc.id_func = mkentry;
	idesc.id_number = parent;
	idesc.id_parent = ino;	/* this is the inode to enter */
	idesc.id_fix = DONTKNOW;
	idesc.id_name = strdup(name);
	dp = ginode(parent);
	if (DIP(dp, di_size) % DIRBLKSIZ) {
		DIP_SET(dp, di_size, roundup(DIP(dp, di_size), DIRBLKSIZ));
		inodirty(dp);
	}
	if ((ckinode(dp, &idesc) & ALTERED) != 0)
		return (1);
	getpathname(pathbuf, parent, parent);
	dp = ginode(parent);
	if (expanddir(dp, pathbuf) == 0)
		return (0);
	return (ckinode(dp, &idesc) & ALTERED);
}