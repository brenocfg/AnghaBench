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
 int /*<<< orphan*/  ack (char*) ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 

void
cwd(char *path)
{

	if (chdir(path) < 0)
		perror_reply(550, path);
	else
		ack("CWD");
}