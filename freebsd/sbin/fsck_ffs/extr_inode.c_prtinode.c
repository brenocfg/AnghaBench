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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int time_t ;
struct passwd {char* pw_name; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 scalar_t__ UFS_ROOTINO ; 
 char* cdevname ; 
 char* ctime (int*) ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_mtime ; 
 int /*<<< orphan*/  di_size ; 
 int /*<<< orphan*/  di_uid ; 
 struct passwd* getpwuid (int) ; 
 scalar_t__ maxino ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
prtinode(ino_t ino, union dinode *dp)
{
	char *p;
	struct passwd *pw;
	time_t t;

	printf(" I=%lu ", (u_long)ino);
	if (ino < UFS_ROOTINO || ino > maxino)
		return;
	printf(" OWNER=");
	if ((pw = getpwuid((int)DIP(dp, di_uid))) != NULL)
		printf("%s ", pw->pw_name);
	else
		printf("%u ", (unsigned)DIP(dp, di_uid));
	printf("MODE=%o\n", DIP(dp, di_mode));
	if (preen)
		printf("%s: ", cdevname);
	printf("SIZE=%ju ", (uintmax_t)DIP(dp, di_size));
	t = DIP(dp, di_mtime);
	p = ctime(&t);
	printf("MTIME=%12.12s %4.4s ", &p[4], &p[20]);
}