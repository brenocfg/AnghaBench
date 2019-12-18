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
 int EINVAL ; 
 int jailparam_del (char*) ; 
 char* mnt_loc ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
jailparam_delarg(char *arg)
{
	char *name, *val;

	if (arg == NULL)
		return (EINVAL);
	name = arg;
	if ((val = strchr(name, '=')) != NULL)
		*val++ = '\0';

	if (strcmp(name, "path") == 0)
		*mnt_loc = '\0';
	return (jailparam_del(name));
}