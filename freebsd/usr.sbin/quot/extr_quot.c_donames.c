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
typedef  int uintmax_t ;
struct fs {int fs_ncg; int fs_ipg; } ;
typedef  int ino_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIP (struct fs*,union dinode*,int /*<<< orphan*/ ) ; 
 int EOF ; 
 int /*<<< orphan*/  di_uid ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ errno ; 
 union dinode* get_inode (int,struct fs*,int) ; 
 int getchar () ; 
 int /*<<< orphan*/  isfree (struct fs*,union dinode*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int scanf (char*,int*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static void
donames(int fd, struct fs *super, char *name)
{
	int c;
	ino_t maxino;
	uintmax_t inode;
	union dinode *dp;

	maxino = super->fs_ncg * super->fs_ipg - 1;
	/* first skip the name of the filesystem */
	while ((c = getchar()) != EOF && (c < '0' || c > '9'))
		while ((c = getchar()) != EOF && c != '\n');
	ungetc(c,stdin);
	while (scanf("%ju", &inode) == 1) {
		if (inode > maxino) {
			warnx("illegal inode %ju", inode);
			return;
		}
		errno = 0;
		if ((dp = get_inode(fd,super,inode))
		    && !isfree(super, dp)) {
			printf("%s\t",user(DIP(super, dp, di_uid))->name);
			/* now skip whitespace */
			while ((c = getchar()) == ' ' || c == '\t');
			/* and print out the remainder of the input line */
			while (c != EOF && c != '\n') {
				putchar(c);
				c = getchar();
			}
			putchar('\n');
		} else {
			if (errno) {
				err(1, "%s", name);
			}
			/* skip this line */
			while ((c = getchar()) != EOF && c != '\n');
		}
		if (c == EOF)
			break;
	}
}