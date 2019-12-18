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
struct inodesc {struct direct* id_dirp; } ;
struct direct {int d_ino; int d_reclen; size_t d_type; char* d_namlen; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int KEEPON ; 
 int diroff ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int,int,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot ; 
 char** typename ; 

int
scannames(struct inodesc *idesc)
{
	struct direct *dirp = idesc->id_dirp;

	printf("slot %d off %d ino %d reclen %d: %s, `%.*s'\n",
	       slot++, diroff, dirp->d_ino, dirp->d_reclen,
	       typename[dirp->d_type], dirp->d_namlen, dirp->d_name);
	diroff += dirp->d_reclen;
	return (KEEPON);
}