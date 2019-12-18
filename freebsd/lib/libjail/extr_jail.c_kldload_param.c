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
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int kldload (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
kldload_param(const char *name)
{
	int kl;

	if (strcmp(name, "linux") == 0 || strncmp(name, "linux.", 6) == 0)
		kl = kldload("linux");
	else if (strcmp(name, "sysvmsg") == 0 || strcmp(name, "sysvsem") == 0 ||
	    strcmp(name, "sysvshm") == 0)
		kl = kldload(name);
	else if (strncmp(name, "allow.mount.", 12) == 0) {
		/* Load the matching filesystem */
		const char *modname = name + 12;

		kl = kldload(modname);
		if (kl < 0 && errno == ENOENT &&
		    strncmp(modname, "no", 2) == 0)
			kl = kldload(modname + 2);
	} else {
		errno = ENOENT;
		return (-1);
	}
	if (kl < 0 && errno == EEXIST) {
		/*
		 * In the module is already loaded, then it must not contain
		 * the parameter.
		 */
		errno = ENOENT;
	}
	return kl;
}