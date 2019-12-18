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

/* Variables and functions */
 int /*<<< orphan*/  M_LOCK ; 
 int getopt (int,char**,char*) ; 
 int pw_userlock (char*,int /*<<< orphan*/ ) ; 

int
pw_user_lock(int argc, char **argv, char *arg1)
{
	int ch;

	while ((ch = getopt(argc, argv, "Cq")) != -1) {
		switch (ch) {
		case 'C':
		case 'q':
			/* compatibility */
			break;
		}
	}

	return (pw_userlock(arg1, M_LOCK));
}