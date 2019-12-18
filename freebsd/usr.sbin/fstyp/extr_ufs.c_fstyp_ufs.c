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
struct fs {int /*<<< orphan*/  fs_volname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  ENOENT 128 
 int /*<<< orphan*/  STDSB ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int sbget (int /*<<< orphan*/ ,struct fs**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

int
fstyp_ufs(FILE *fp, char *label, size_t labelsize)
{
	struct fs *fs;

	switch (sbget(fileno(fp), &fs, STDSB)) {
	case 0:
		strlcpy(label, fs->fs_volname, labelsize);
		return (0);
	case ENOENT:
		/* Cannot find file system superblock */
		return (1);
	default:
		/* Unable to read file system superblock */
		return (1);
	}
}