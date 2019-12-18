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
 int add_file (int,char*,int,int) ; 
 int delete_file (int,char*,int,int) ; 

__attribute__((used)) static int
do_file(int agent_fd, int deleting, int key_only, char *file, int qflag)
{
	if (deleting) {
		if (delete_file(agent_fd, file, key_only, qflag) == -1)
			return -1;
	} else {
		if (add_file(agent_fd, file, key_only, qflag) == -1)
			return -1;
	}
	return 0;
}