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
typedef  int u_int ;

/* Variables and functions */
#define  S_IFBLK 135 
#define  S_IFCHR 134 
#define  S_IFDIR 133 
#define  S_IFDOOR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 

const char *
inotype(u_int type)
{

	switch (type & S_IFMT) {
	case S_IFBLK:
		return ("block");
	case S_IFCHR:
		return ("char");
	case S_IFDIR:
		return ("dir");
	case S_IFIFO:
		return ("fifo");
	case S_IFREG:
		return ("file");
	case S_IFLNK:
		return ("link");
#ifdef S_IFSOCK
	case S_IFSOCK:
		return ("socket");
#endif
#ifdef S_IFDOOR
	case S_IFDOOR:
		return ("door");
#endif
	default:
		return ("unknown");
	}
	/* NOTREACHED */
}