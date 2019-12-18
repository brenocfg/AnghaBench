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
 int /*<<< orphan*/  LOGCMD (char*,char*) ; 
 char* doublequote (char*) ; 
 int /*<<< orphan*/  fatalerror (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ guest ; 
 scalar_t__ mkdir (char*,int) ; 
 scalar_t__ noguestmkd ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*,...) ; 

void
makedir(char *name)
{
	char *s;

	LOGCMD("mkdir", name);
	if (guest && noguestmkd)
		reply(550, "Operation not permitted.");
	else if (mkdir(name, 0777) < 0)
		perror_reply(550, name);
	else {
		if ((s = doublequote(name)) == NULL)
			fatalerror("Ran out of memory.");
		reply(257, "\"%s\" directory created.", s);
		free(s);
	}
}