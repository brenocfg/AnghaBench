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
struct fs {int dummy; } ;

/* Variables and functions */
#define  ENOENT 128 
 int /*<<< orphan*/  STDSB ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  func (int,struct fs*,char*) ; 
 int /*<<< orphan*/  get_inode (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initfsizes () ; 
 int /*<<< orphan*/  inituser () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int sbget (int,struct fs**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,struct fs*,char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

void
quot(char *name, char *mp)
{
	int fd;
	struct fs *fs;

	get_inode(-1, NULL, 0);		/* flush cache */
	inituser();
	initfsizes();
	if ((fd = open(name,0)) < 0) {
		warn("%s", name);
		close(fd);
		return;
	}
	switch (sbget(fd, &fs, STDSB)) {
	case 0:
		break;
	case ENOENT:
		warn("Cannot find file system superblock");
		close(fd);
		return;
	default:
		warn("Unable to read file system superblock");
		close(fd);
		return;
	}
	printf("%s:",name);
	if (mp)
		printf(" (%s)",mp);
	putchar('\n');
	(*func)(fd, fs, name);
	close(fd);
}