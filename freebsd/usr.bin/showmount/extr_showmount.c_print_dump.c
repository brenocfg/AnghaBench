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
struct mountlist {char* ml_host; char* ml_dirp; struct mountlist* ml_right; struct mountlist* ml_left; } ;

/* Variables and functions */
#define  ALL 129 
#define  DIRS 128 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int type ; 

void
print_dump(struct mountlist *mp)
{

	if (mp == NULL)
		return;
	if (mp->ml_left)
		print_dump(mp->ml_left);
	switch (type) {
	case ALL:
		printf("%s:%s\n", mp->ml_host, mp->ml_dirp);
		break;
	case DIRS:
		printf("%s\n", mp->ml_dirp);
		break;
	default:
		printf("%s\n", mp->ml_host);
		break;
	}
	if (mp->ml_right)
		print_dump(mp->ml_right);
}