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
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 int DIP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IFBLK 134 
#define  IFCHR 133 
#define  IFDIR 132 
#define  IFIFO 131 
#define  IFLNK 130 
 int IFMT ; 
#define  IFREG 129 
#define  IFSOCK 128 
 int /*<<< orphan*/  checkactive () ; 
 int /*<<< orphan*/  curinode ; 
 int /*<<< orphan*/  curinum ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printstat (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prtblknos (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
printactive(int doblocks)
{
    if (!checkactive())
	return 1;
    switch (DIP(curinode, di_mode) & IFMT) {
    case IFDIR:
    case IFREG:
    case IFBLK:
    case IFCHR:
    case IFLNK:
    case IFSOCK:
    case IFIFO:
	if (doblocks)
	    prtblknos(&disk, curinode);
	else
	    printstat("current inode", curinum, curinode);
	break;
    case 0:
	printf("current inode %ju: unallocated inode\n", (uintmax_t)curinum);
	break;
    default:
	printf("current inode %ju: screwy itype 0%o (mode 0%o)?\n",
	    (uintmax_t)curinum, DIP(curinode, di_mode) & IFMT,
	    DIP(curinode, di_mode));
	break;
    }
    return 0;
}