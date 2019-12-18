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

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
#define  IFBLK 134 
#define  IFCHR 133 
#define  IFDIR 132 
#define  IFIFO 131 
#define  IFLNK 130 
 int IFMT ; 
#define  IFREG 129 
#define  IFSOCK 128 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
ftypeok(union dinode *dp)
{
	switch (DIP(dp, di_mode) & IFMT) {

	case IFDIR:
	case IFREG:
	case IFBLK:
	case IFCHR:
	case IFLNK:
	case IFSOCK:
	case IFIFO:
		return (1);

	default:
		if (debug)
			printf("bad file type 0%o\n", DIP(dp, di_mode));
		return (0);
	}
}