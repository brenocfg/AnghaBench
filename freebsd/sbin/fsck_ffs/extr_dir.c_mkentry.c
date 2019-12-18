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
struct inodesc {scalar_t__ id_parent; int /*<<< orphan*/  id_name; struct direct* id_dirp; } ;
struct direct {scalar_t__ d_ino; int d_reclen; scalar_t__ d_namlen; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  ino_type; } ;

/* Variables and functions */
 int ALTERED ; 
 int DIRSIZ (int /*<<< orphan*/ ,struct direct*) ; 
 int KEEPON ; 
 int STOP ; 
 TYPE_1__* inoinfo (scalar_t__) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mkentry(struct inodesc *idesc)
{
	struct direct *dirp = idesc->id_dirp;
	struct direct newent;
	int newlen, oldlen;

	newent.d_namlen = strlen(idesc->id_name);
	newlen = DIRSIZ(0, &newent);
	if (dirp->d_ino != 0)
		oldlen = DIRSIZ(0, dirp);
	else
		oldlen = 0;
	if (dirp->d_reclen - oldlen < newlen)
		return (KEEPON);
	newent.d_reclen = dirp->d_reclen - oldlen;
	dirp->d_reclen = oldlen;
	dirp = (struct direct *)(((char *)dirp) + oldlen);
	dirp->d_ino = idesc->id_parent;	/* ino to be entered is in id_parent */
	dirp->d_reclen = newent.d_reclen;
	dirp->d_type = inoinfo(idesc->id_parent)->ino_type;
	dirp->d_namlen = newent.d_namlen;
	memmove(dirp->d_name, idesc->id_name, (size_t)newent.d_namlen + 1);
	return (ALTERED|STOP);
}