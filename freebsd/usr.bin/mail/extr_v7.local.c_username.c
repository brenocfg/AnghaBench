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
typedef  scalar_t__ uid_t ;

/* Variables and functions */
 char* getenv (char*) ; 
 char* getname (scalar_t__) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

char *
username(void)
{
	char *np;
	uid_t uid;

	if ((np = getenv("USER")) != NULL)
		return (np);
	if ((np = getenv("LOGNAME")) != NULL)
		return (np);
	if ((np = getname(uid = getuid())) != NULL)
		return (np);
	printf("Cannot associate a name with uid %u\n", (unsigned)uid);
	return (NULL);
}