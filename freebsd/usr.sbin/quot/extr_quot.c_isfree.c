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
struct fs {int dummy; } ;

/* Variables and functions */
 int DIP (struct fs*,union dinode*,int /*<<< orphan*/ ) ; 
#define  IFBLK 135 
#define  IFCHR 134 
#define  IFDIR 133 
#define  IFIFO 132 
#define  IFLNK 131 
 int IFMT ; 
#define  IFREG 130 
#define  IFSOCK 129 
#define  IFWHT 128 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 

__attribute__((used)) static int
isfree(struct fs *super, union dinode *dp)
{
#ifdef	COMPAT
	return (DIP(super, dp, di_mode) & IFMT) == 0;
#else	/* COMPAT */

	switch (DIP(super, dp, di_mode) & IFMT) {
	case IFIFO:
	case IFLNK:		/* should check FASTSYMLINK? */
	case IFDIR:
	case IFREG:
		return 0;
	case IFCHR:
	case IFBLK:
	case IFSOCK:
	case IFWHT:
	case 0:
		return 1;
	default:
		errx(1, "unknown IFMT 0%o", DIP(super, dp, di_mode) & IFMT);
	}
#endif
}