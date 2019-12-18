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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int errno ; 
 scalar_t__ gethostname (char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
nb_getlocalname(char *name)
{
	char buf[1024], *cp;

	if (gethostname(buf, sizeof(buf)) != 0)
		return errno;
	cp = strchr(buf, '.');
	if (cp)
		*cp = 0;
	strcpy(name, buf);
	return 0;
}