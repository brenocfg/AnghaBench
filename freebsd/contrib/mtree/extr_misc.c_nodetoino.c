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
#define  F_BLOCK 134 
#define  F_CHAR 133 
#define  F_DIR 132 
#define  F_FIFO 131 
#define  F_FILE 130 
#define  F_LINK 129 
#define  F_SOCK 128 
 int S_IFBLK ; 
 int S_IFCHR ; 
 int S_IFDIR ; 
 int S_IFIFO ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 int S_IFSOCK ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*,int) ; 

u_int
nodetoino(u_int type)
{

	switch (type) {
	case F_BLOCK:
		return S_IFBLK;
	case F_CHAR:
		return S_IFCHR;
	case F_DIR:
		return S_IFDIR;
	case F_FIFO:
		return S_IFIFO;
	case F_FILE:
		return S_IFREG;
	case F_LINK:
		return S_IFLNK;
#ifdef S_IFSOCK
	case F_SOCK:
		return S_IFSOCK;
#endif
	default:
		printf("unknown type %d", type);
		abort();
	}
	/* NOTREACHED */
}