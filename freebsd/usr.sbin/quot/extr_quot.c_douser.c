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
struct user {char* name; int /*<<< orphan*/  spc90; int /*<<< orphan*/  spc60; int /*<<< orphan*/  spc30; scalar_t__ count; int /*<<< orphan*/  space; } ;
struct fs {int fs_ncg; int fs_ipg; } ;
typedef  int ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIP (struct fs*,union dinode*,int /*<<< orphan*/ ) ; 
 int SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  actualblocks (struct fs*,union dinode*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct user*,int) ; 
 scalar_t__ count ; 
 int /*<<< orphan*/  di_atime ; 
 int /*<<< orphan*/  di_uid ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ estimate ; 
 int /*<<< orphan*/  free (struct user*) ; 
 union dinode* get_inode (int,struct fs*,int) ; 
 int /*<<< orphan*/  isfree (struct fs*,union dinode*) ; 
 scalar_t__ malloc (int) ; 
 int nusers ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sortusers (struct user*) ; 
 scalar_t__ unused ; 
 int /*<<< orphan*/  users ; 
 int /*<<< orphan*/  uses (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtualblocks (struct fs*,union dinode*) ; 

__attribute__((used)) static void
douser(int fd, struct fs *super, char *name)
{
	ino_t inode, maxino;
	struct user *usr, *usrs;
	union dinode *dp;
	int n;

	maxino = super->fs_ncg * super->fs_ipg - 1;
	for (inode = 0; inode < maxino; inode++) {
		errno = 0;
		if ((dp = get_inode(fd,super,inode))
		    && !isfree(super, dp))
			uses(DIP(super, dp, di_uid),
			    estimate ? virtualblocks(super, dp) :
				actualblocks(super, dp),
			    DIP(super, dp, di_atime));
		else if (errno) {
			err(1, "%s", name);
		}
	}
	if (!(usrs = (struct user *)malloc(nusers * sizeof(struct user))))
		errx(1, "allocate users");
	bcopy(users,usrs,nusers * sizeof(struct user));
	sortusers(usrs);
	for (usr = usrs, n = nusers; --n >= 0 && usr->count; usr++) {
		printf("%5d",SIZE(usr->space));
		if (count)
			printf("\t%5ld",usr->count);
		printf("\t%-8s",usr->name);
		if (unused)
			printf("\t%5d\t%5d\t%5d",
			       SIZE(usr->spc30),
			       SIZE(usr->spc60),
			       SIZE(usr->spc90));
		printf("\n");
	}
	free(usrs);
}