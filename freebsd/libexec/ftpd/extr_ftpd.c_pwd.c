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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 char* doublequote (char*) ; 
 int /*<<< orphan*/  fatalerror (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*,char*) ; 

void
pwd(void)
{
	char *s, path[MAXPATHLEN + 1];

	if (getcwd(path, sizeof(path)) == NULL)
		perror_reply(550, "Get current directory");
	else {
		if ((s = doublequote(path)) == NULL)
			fatalerror("Ran out of memory.");
		reply(257, "\"%s\" is current directory.", s);
		free(s);
	}
}